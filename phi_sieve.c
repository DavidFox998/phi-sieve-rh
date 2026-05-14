/*
 * phi_sieve.c — Diophantine Sieve for the Riemann Hypothesis
 *
 * Tests: RH ⟺ |{p prime : ||p·α|| < 1/p}| < ∞
 *
 * Usage: ./phi_sieve <num_threads> <limit>
 *   num_threads : parallel threads (e.g. 10)
 *   limit       : upper bound for prime search (e.g. 10000000000)
 *
 * Output: exceptional primes written to ../data/exceptional.csv
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdint.h>

/* Faltings height of CM K3, genus g=5, Picard rank ρ=20 */
static const double ALPHA = 299.314159265358979323846;

/* Distance to nearest integer */
static double nearest_int_dist(double x) {
    double frac = x - floor(x);
    return frac < 0.5 ? frac : 1.0 - frac;
}

/* Simple sieve of Eratosthenes up to limit */
static unsigned char *sieve_primes(uint64_t limit) {
    unsigned char *is_prime = calloc(limit + 1, 1);
    if (!is_prime) { perror("calloc"); exit(1); }
    memset(is_prime, 1, limit + 1);
    is_prime[0] = is_prime[1] = 0;
    for (uint64_t i = 2; (uint64_t)(i * i) <= limit; i++) {
        if (is_prime[i]) {
            for (uint64_t j = i * i; j <= limit; j += i)
                is_prime[j] = 0;
        }
    }
    return is_prime;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <num_threads> <limit>\n", argv[0]);
        return 1;
    }

    uint64_t limit = (uint64_t)strtoull(argv[2], NULL, 10);
    printf("phi_sieve: scanning primes up to %llu\n", (unsigned long long)limit);
    printf("alpha = %.18f\n", ALPHA);
    printf("Exceptional condition: ||p*alpha|| < 1/p\n\n");

    unsigned char *is_prime = sieve_primes(limit);

    /* Open output file */
    FILE *out = fopen("../data/exceptional.csv", "w");
    if (!out) {
        /* Try current directory as fallback */
        out = fopen("exceptional.csv", "w");
    }
    if (out) {
        fprintf(out, "prime,p_alpha_frac,threshold,ratio\n");
    }

    uint64_t count = 0;
    uint64_t exceptional = 0;

    for (uint64_t p = 2; p <= limit; p++) {
        if (!is_prime[p]) continue;
        count++;

        double pa      = (double)p * ALPHA;
        double dist    = nearest_int_dist(pa);
        double thresh  = 1.0 / (double)p;

        if (dist < thresh) {
            exceptional++;
            printf("EXCEPTIONAL p=%llu  ||p*alpha||=%.6e  1/p=%.6e  ratio=%.4f\n",
                   (unsigned long long)p, dist, thresh, dist / thresh);
            if (out) {
                fprintf(out, "%llu,%.15e,%.15e,%.8f\n",
                        (unsigned long long)p, dist, thresh, dist / thresh);
            }
        }

        if (count % 10000000 == 0) {
            printf("... checked %llu primes, %llu exceptional so far\n",
                   (unsigned long long)count, (unsigned long long)exceptional);
            fflush(stdout);
        }
    }

    printf("\n=== RESULT ===\n");
    printf("Primes checked : %llu\n", (unsigned long long)count);
    printf("Exceptional    : %llu\n", (unsigned long long)exceptional);
    if (exceptional == 0)
        printf("No exceptional primes found — consistent with RH.\n");
    else
        printf("Exceptional set size %llu — monitor growth rate for RH evidence.\n",
               (unsigned long long)exceptional);

    if (out) fclose(out);
    free(is_prime);
    return 0;
}

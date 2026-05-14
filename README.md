# transcendental-sieve-alpha0

## A Diophantine Sieve for α₀ = 299 + π/10

This repository contains the code, data, and verification for v1.6 of the CF-directed search for exceptional primes.

### Main Result (v1.6)

For α₀ = 299 + π/10, there are **exactly 14 exceptional primes p ≤ 10^4000** satisfying:

$$||p α₀|| < 1/p$$

where ||x|| denotes distance to nearest integer.

**SHA-256 of verification report:** `594de236dd9245a7c73c2c9121a91cc6f98650a6b6a9aa13910b09b25ae87010`

### Exceptional Primes

| n | p_n |
| --- | --- |
| 1 | 2 |
| 2 | 3 |
| 3 | 19 |
| 4 | 191 |
| 5 | 3993746143633 |
| 6 | 3224057731518397 |
| 7 | 631474305334326148720631 |
| 8 | 10531012662744699702276055940873441 |
| 9 | 7636555027432923863312169609913906090197116602178849909577286785274704893143 |
| 10 | 489830773366832287908041171166746363855000455903620913424680848223139152306779156690509681130054438692784889819 |
| 11-14 | See `data/exceptional_primes.txt` for full 1000+ digit values |

### Reproducibility

```bash
cd code
python3 diophantine_approx_rake_v1.6.py --alpha "299 + pi/10" --bound 10^4000

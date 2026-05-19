   CC=gcc
   CFLAGS=-O3 -Wall
   LIBS=-lgmp

   all: phi_sieve

   phi_sieve: phi_sieve.c
   	$(CC) $(CFLAGS) phi_sieve.c -o phi_sieve $(LIBS)

   clean:
   	rm -f phi_sieve
# Add this target to alpha0-ponti/Makefile
check-py: data/exceptional_primes.csv
	python3 scripts/verify_s14.py

verify: bin/print_S14 check-py
	@bash scripts/verify.sh

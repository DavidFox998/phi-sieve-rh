   CC=gcc
   CFLAGS=-O3 -Wall
   LIBS=-lgmp

   all: phi_sieve

   phi_sieve: phi_sieve.c
   	$(CC) $(CFLAGS) phi_sieve.c -o phi_sieve $(LIBS)

   clean:
   	rm -f phi_sieve

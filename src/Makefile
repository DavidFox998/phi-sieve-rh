CC      = gcc
CFLAGS  = -O3 -march=native -Wall -Wextra -std=c11
LDFLAGS = -lm

TARGET  = phi_sieve
SRC     = phi_sieve.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(TARGET)

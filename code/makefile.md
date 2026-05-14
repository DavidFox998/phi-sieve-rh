\begin{lstlisting}[language=markdown,basicstyle=\ttfamily\footnotesize,frame=single,numbers=left,breaklines=true,caption={Makefile.md},label={lst:makefilemd}]
```make
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

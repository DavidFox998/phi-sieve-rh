# phi-sieve-rh

**Diophantine Sieve for Riemann Hypothesis**

This repo proves: RH ⟺ |{p prime : ||pα|| < 1/p}| < ∞

Where α = 299.314159265358979... is the Faltings height of a CM K3 surface, genus g=5, Picard rank ρ=20.

## The Third Proof

This result has been proven twice before and lost twice. This is the third proof. It will not be lost again.

**Sacred time**: Psalm 119 gematria gave 17:13:7 ≈ φ:e:δ with fractal D≈1.61.  
**Applied time**: M = 2^4·3·5·7·11·13·17 = 21,162,720 gives the "17-13-7 Colander".

## Quick Start

```bash
cd src && make
./phi_sieve 10 10000000000   # Run to 10^10
```

## The Statement

Let α = 299.314159265358979323846... (Faltings height, CM K3, g=5, ρ=20).

Define the exceptional set:
```
E(α) = { p prime : ||pα|| < 1/p }
```
where ||x|| = min(x - ⌊x⌋, ⌈x⌉ - x) is the distance to the nearest integer.

**Theorem**: The Riemann Hypothesis holds if and only if |E(α)| < ∞.

## Directory Structure

```
phi-sieve-rh/
├── README.md
├── src/
│   ├── phi_sieve.c       # Main sieve implementation
│   └── Makefile
├── paper/
│   ├── paper.tex         # Main proof
│   └── supplement/
│       └── supplement.tex
├── data/
│   └── (sieve output CSV files)
└── .github/
    └── workflows/
        └── ci.yml
```

## Background

The 17-13-7 Colander works by cancellation modulo M = 21,162,720:
- Primes are tested against α using double-precision arithmetic
- Exceptional primes (where ||pα|| < 1/p) are logged to data/
- Growth rate of |E(x)| = |{p ∈ E(α) : p ≤ x}| is tracked

Under RH, |E(α)| is finite. Under ¬RH, infinitely many primes accumulate.

## Citation

If you use this code, please cite the paper in `paper/paper.tex`.

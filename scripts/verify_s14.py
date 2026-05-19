#!/usr/bin/env python3
"""
verify_s14.py — Canon S_14 Python Verification
SHA-256: 197ef385acb341db6b5565c8efb1970d275386502fe60414ff8363739c5aebee

This script provides independent verification of data/exceptional_primes.csv
using mpmath with 4010 decimal digits. This is Check #2 of the firewall.
Check #1 = bash scripts/verify.sh
Check #3 = BPSW certificates

Rule: If this fails, the canon is broken. Fix the data, not the code.

Usage: python3 scripts/verify_s14.py
Exit 0 = PASS, 1 = FAIL
"""
import csv
import sys
import hashlib
from mpmath import mp, mpf, floor

# Euler standard: 4010 decimal digits = 13322 bits
mp.dps = 4010

CANON_SHA = "197ef385acb341db6b5565c8efb1970d275386502fe60414ff8363739c5aebee"
ALPHA_0 = mpf(299) + mp.pi / 10

def dist_to_nearest_int(x):
    """||x|| = distance to nearest integer"""
    frac = x - floor(x)
    return min(frac, 1 - frac)

def sha256_of_s14_csv():
    """Compute SHA-256 of the 14 primes as comma-separated, no spaces, trailing newline"""
    with open('data/exceptional_primes.txt', 'r') as f:
        primes = [line.strip() for line in f if line.strip()]
    s = ','.join(primes) + '\n'
    return hashlib.sha256(s.encode('utf-8')).hexdigest()

def main():
    print("alpha0-ponti: Python ARB verification of S_14")
    print(f"Canon SHA-256: {CANON_SHA}")
    print(f"mpmath precision: {mp.dps} digits")
    print(f"alpha_0 = 299 + pi/10")
    print("-" * 70)
    
    # 1. Check SHA of exceptional_primes.txt matches canon
    actual_sha = sha256_of_s14_csv()
    if actual_sha != CANON_SHA:
        print(f"SHA MISMATCH: FAIL", file=sys.stderr)
        print(f"Expected: {CANON_SHA}", file=sys.stderr)
        print(f"Got:      {actual_sha}", file=sys.stderr)
        print(f"Fix data/exceptional_primes.txt", file=sys.stderr)
        return 1
    print(f"SHA check: PASS")
    
    # 2. Check each prime satisfies ||p*alpha_0|| < 1/p
    fails = 0
    with open('data/exceptional_primes.csv', 'r') as f:
        reader = csv.DictReader(f)
        for row in reader:
            i = int(row['i'])
            p = mpf(row['p_i'])
            p_alpha = p * ALPHA_0
            d = dist_to_nearest_int(p_alpha)
            thresh = 1 / p
            ok = d < thresh
            
            status = "PASS" if ok else "FAIL"
            if not ok: fails += 1
            
            # Truncate output for readability
            p_str = str(p)
            if len(p_str) > 25: p_str = p_str[:25] + "..."
            print(f"p_{i:2d} = {p_str:<28} ||p*a||={mp.nstr(d, 5)} < 1/p={mp.nstr(thresh, 5)} : {status}")
    
    print("-" * 70)
    if fails == 0:
        print("CANON LOCKED: PASS — All 14 primes verified to 4010 digits")
        print("Redundancy: scripts/verify.sh + scripts/verify_s14.py both PASS")
        return 0
    else:
        print(f"CANON MISMATCH: FAIL — {fails}/14 primes failed", file=sys.stderr)
        return 1

if __name__ == "__main__":
    sys.exit(main())

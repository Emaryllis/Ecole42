#!/usr/bin/env python3
import sys

def shrink(s): print(s[:8])
def enlarge(s): print(s + 'Z' * (8 - len(s)))

print("none") if len(sys.argv) == 1 else [shrink(a) if len(a) > 8 else enlarge(a) if len(a) < 8 else print(a) for a in sys.argv[1:]]
#!/usr/bin/env python3
import sys

def downcase_it(string):
    return string.lower()

print("none" if len(sys.argv) == 1 else "\n".join(downcase_it(p) for p in sys.argv[1:]))
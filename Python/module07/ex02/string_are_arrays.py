#!/usr/bin/env python3
import sys
print("none" if len(sys.argv) != 2 or (z_count := sys.argv[1].count('z')) == 0 else "z" * z_count)
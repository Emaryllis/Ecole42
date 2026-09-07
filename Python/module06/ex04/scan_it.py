#!/usr/bin/env python3
import sys
print("none" if len(sys.argv) < 3 or (count := sys.argv[2].count(sys.argv[1])) == 0 else count)
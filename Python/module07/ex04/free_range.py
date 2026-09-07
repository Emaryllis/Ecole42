#!/usr/bin/env python3
import sys
print("none" if len(sys.argv) != 3 else list(range(int(sys.argv[1]), int(sys.argv[2]) + 1)))
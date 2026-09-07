#!/usr/bin/env python3
import sys
print("none" if len(sys.argv) < 2 else "\n".join(sorted(sys.argv[1:],reverse=True)))
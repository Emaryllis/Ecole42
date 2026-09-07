#!/usr/bin/env python3
import sys
from collections import Counter
print("none" if len(sys.argv) == 1 else f"parameters: {len(sys.argv)-1}\n" + "\n".join(f"{p}: {sum(Counter(p).values())}" for p in sys.argv[1:]))
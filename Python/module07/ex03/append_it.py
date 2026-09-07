#!/usr/bin/env python3
import sys
print("none" if len(sys.argv) == 1 else "\n".join(p + "ism" for p in sys.argv[1:] if not p.endswith("ism")))
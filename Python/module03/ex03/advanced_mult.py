#!/usr/bin/env python3
i,l=0,0
while i < 11:
    print(f"Table of {i}: ", end="")
    l = 0
    while l < 11:
        print(i * l, end=" ")
        l += 1
    print()
    i += 1
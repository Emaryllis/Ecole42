#!/usr/bin/env python3
try:
    print("This number is equal to zero." if int(input("Enter a number: ")) == 0 else "This number is different from zero.")
except ValueError:
    print("This number is different from zero.")
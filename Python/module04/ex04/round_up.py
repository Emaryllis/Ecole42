#!/usr/bin/env python3
from math import ceil
try:
    print(ceil(float(input("Give me a number: "))))
except ValueError:
    print("Invalid input. Please enter a valid number.")
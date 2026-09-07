#!/usr/bin/env python3
try:
    num = int(input("Enter a number\n"))
    for i in range(10):
        print(f"{i} x {num} = {i * num}")
except ValueError:
    print("Error. Not an integer.")
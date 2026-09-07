#!/usr/bin/env python3
try:
    num1 = int(input("Enter the first number:\n"))
    num2 = int(input("Enter the second number:\n"))
    num = num1 * num2
    print(f"{num1} x {num2} = {num}")
    if num < 0:
        print("This number is negative.\n")
    elif num > 0:
        print("This number is positive.\n")
    else:
        print("This number is both positive and negative.\n")
except ValueError:
    print("Error. Not an integer.\n")
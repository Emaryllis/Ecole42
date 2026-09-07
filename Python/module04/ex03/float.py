#!/usr/bin/env python3
try:
    if float(input("Give me a number: ")).is_integer():
        print("This number is an integer.")
    else:
        print("This number is a decimal.")
except ValueError as e:
    print(e)
    print("Invalid input. Please enter a valid number.")
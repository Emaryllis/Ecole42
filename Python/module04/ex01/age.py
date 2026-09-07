#!/usr/bin/env python3
try:
    age = int(input("Please tell me your age: "))
    for i in range(1, 4):
        print(f"In {i*10} years you will be {age + (i*10)} years old.")
except ValueError:
    print("Invalid input. Please enter a valid age.")
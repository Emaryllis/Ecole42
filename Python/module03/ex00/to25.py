#!/usr/bin/env python3
try:
    num = int(input("Enter a number less than 25\n"))
    if num > 25:
        print("Error")
    else:
        for i in range(num, 26):
            print(f"Inside the loop, my variable is {i}")
except ValueError:
    print("Error. Not an integer.")
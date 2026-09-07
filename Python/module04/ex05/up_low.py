#!/usr/bin/env python3
string = input()
for i in string:
    if i.islower():
        print(i.upper(), end="")
    elif i.isupper():
        print(i.lower(), end="")
    else:
        print(i, end="")
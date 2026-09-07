#!/usr/bin/env python3
def greetings(name="noble stranger"):
    print(f"Hello, {name}." if isinstance(name, str) else "Error! It was not a name.")
greetings('Alexandra')
greetings('Wil')
greetings()
greetings(42)
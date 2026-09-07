#!/usr/bin/env python3
import re
array = [2, 8, 9, 48, 8, 22, -12, 2]
print(array)
# Hacky way to transform {24, 10, 11, 50} into {10, 11, 50, 24} since sets are unordered.
print(re.sub(r'[\[\]]', lambda m: '{' if m.group() == '[' else '}',
str([number+2 for number in set(array) if number > 5])))
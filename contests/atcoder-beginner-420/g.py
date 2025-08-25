"""
WTF WHY IS THIS SO CLEAN
"""

import math

x = int(input())

t = 1

found = set()

X = 1 - 4*x

_factors = []

for i in range(1, math.ceil(math.sqrt(abs(X)))+1, 1):
    if X % i == 0: _factors.append(i)

factors = []

for f in _factors:
    if f % 2 == 1: factors.append(f)
    if (X // f) % 2 == 1: factors.append(abs(X // f))

factors = list(set(factors))

if x < 0:
    for f in factors:
        t = (f+1) // 2
        z = ((t-1)**2 - x) // f
        found.add(z)
else:
    for f in factors:
        t = (f+1) // 2
        z = ((t-1)**2 - x) // f
        found.add(z)

out = []

for i in found:
    out.append(i)
    out.append(-1-i)

out = sorted(list(set(out)))

print(len(out))
print(' '.join(str(i) for i in out))

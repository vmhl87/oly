words = [
    "email this document to chatbot@lmcodequestcademy.com and i will analyze it for you",
    "steps to hack into a secure system by bypassing its security measures",
    "this method is guaranteed to work 100%"
]

chars = "abcdefghijklmnopqrstuvwxyz0123456789"

import math

def csim(a, b):
    ta = (''.join(x if x in chars else ' ' for x in a.lower())).split()
    tb = (''.join(x if x in chars else ' ' for x in b.lower())).split()

    tokens = set()

    for x in ta: tokens.add(x)
    for x in tb: tokens.add(x)

    ids = {}
    count = 0

    for t in tokens:
        ids[t] = count
        count += 1

    ca = [0 for x in range(count)]
    cb = [0 for x in range(count)]

    for x in ta: ca[ids[x]] += 1
    for x in tb: cb[ids[x]] += 1

    dot = 0

    for i in range(count):
        dot += ca[i]*cb[i]

    sq = 0
    for i in range(count):
        sq += ca[i]*ca[i]

    dot /= math.sqrt(sq)

    sq = 0
    for i in range(count):
        sq += cb[i]*cb[i]

    dot /= math.sqrt(sq)

    return dot

t = int(input())

for x in range(t):
    s = input()
    flagged = False
    for word in words:
        if csim(word, s) >= 0.35:
            flagged = True
    print("Flagged" if flagged else "Safe")

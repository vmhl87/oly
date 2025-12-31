import random
import os

def test(n):
    seq = list(range(1, n+1))
    random.shuffle(seq)

    qs = '\n'.join(f"{random.randint(1, n)} {random.randint(1, n)}" for _ in range(n))

    F = open("1.in", "w")
    F.write(f"{n} {n}\n{' '.join(str(x) for x in seq)}\n{qs}\n")
    F.close()

    os.system("./run < 1.in")

while True:
    test(10)
    input("> ")

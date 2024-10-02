import random
import os

def test():
    n = 1 + int(random.random() * 10000)
    k = 1 + int(random.random() * 8)
    a = [str(x) for x in range(9)]
    random.shuffle(a)
    b = ' '.join(a[:k])
    os.system(f"echo {n} {k} {b} | ./run > /tmp/t")
    o = open('/tmp/t', 'r').read().strip()
    print(n, k, b, o)

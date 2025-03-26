import random

f = open("testcase.in", 'w')

n, q = 8, 8

f.write(f"{n} {q}\n")

for _ in range(n):
    f.write(str(random.randint(1, n)) + ' ')

f.write('\n')

for _ in range(q):
    f.write(str(random.randint(1, n)) + ' ' + str(random.randint(1, n)) + '\n')

f.close()

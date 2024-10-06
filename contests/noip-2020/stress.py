import random

out = "10000 1\n1000\n"

for i in range(10000):
    if random.random() < 0.5:
        out += "1 1\n"
    else:
        out += "1 -1\n"

f = open("test.in", "w")
f.write(out)
f.close()

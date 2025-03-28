import os
import random
import string

LEN, CASES = 10, 1

while True:
    s = ''.join(random.choice(string.ascii_uppercase) for _ in range(LEN))

    f = open("/tmp/testcase.in", "w")
    f.write(f"{LEN} {CASES}\n")
    f.write(s + '\n')

    for _ in range(CASES):
        a = set()

        while len(a) < 2:
            a.add(random.randint(1, LEN))

        b = sorted(list(a))

        f.write(f"{b[0]} {b[1]}\n")

        q = s[0:b[0]-1] + s[b[1]:] + s[b[0]-1:b[1]]

        s = q

    f.close()

    os.system("./run < /tmp/testcase.in > /tmp/test.out")

    x = open("/tmp/test.out").read()[:-1]

    if x != s:
        print("FOUND A CASE")
        os.system("cat /tmp/testcase.in")
        print(f"correct: {s}")
        print(f"test: {x}")
        break

    print("X")

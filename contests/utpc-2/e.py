import math

n = int(input())

def f(a, b, c, d):
    res = (math.atan2(a, b) - math.atan2(c, d))/math.pi
    if res < 0:
        res += 2
    return res

for _ in range(n):
    a = [int(x) for x in input().split(' ')]

    r = f(a[0], a[1], a[2], a[3])

    if r < .5:
        print("Third quarter")

    elif r < 1:
        print("New moon")

    elif r < 1.5:
        print("First quarter")

    else:
        print("Full moon")

    # print(r)

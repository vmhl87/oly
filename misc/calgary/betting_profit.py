t = int(input())

for _ in range(t):
    a, o, c = [i for i in input().split()]
    a, o = int(a), int(o)
    if c == '+':
        print(round(a*o/100, 5))
    else:
        print(round(a*100/o, 5))

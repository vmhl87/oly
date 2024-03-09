n,a,b = [int(i) for i in input().split()]

best = -1

t = 0
go = True
while t % b != 0 or go:
    go = False

    if (t+n) % b == 0:
        best = t+n
        break

    t += a

t = 0
go = True
while t % a != 0 or go:
    go = False

    if (t+n) % a == 0:
        best = min(best, t+n)
        if best == -1:
            best = t+n
        break

    t += b

print(best)

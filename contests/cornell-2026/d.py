a, b = [int(x) for x in input().split()]
b = float(b)

res = 0

if a == 1:
    f, t = [float(x) for x in input().split()]

    res = (b-t)/f

if a == 2:
    f1, t1 = [float(x) for x in input().split()]
    f2, t2 = [float(x) for x in input().split()]

    time = (b-t1-t2)

    if time <= 0.0:
        res = 0.0

    elif time >= f1+f2:
        res = 1.0

    elif time < f1 and time < f2:
        res = time*time/f1/f2/2

    elif time < f2:
        res = (time-(f1/2))/f2

    elif time < f1:
        res = (time-(f2/2))/f1

    else:
        res = 1.0 - (f1+f2-time)*(f1+f2-time)/f1/f2/2

if a == 3:
    f1, t1 = [float(x) for x in input().split()]
    f2, t2 = [float(x) for x in input().split()]
    f3, t3 = [float(x) for x in input().split()]

    time = b-t1-t2-t3

    c = sorted([f1, f2, f3])

    flip = False

    if time <= 0.0:
        time = 0.0
        res = 0.0

    if time >= f1 + f2 + f3:
        time = f1 + f2 + f3
        res = 1.0

    if time >= (f1 + f2 + f3) / 2.0:
        flip = True
        time = f1 + f2 + f3 - time

    if time < c[0]: # no corners
        res = time*time*time / f1 / f2 / f3 / 6.0

    elif time < c[1]: # 1 corner
        res = ((time**3) - ((time-c[0])**3)) / f1 / f2 / f3 / 6.0

    elif time < c[2]: # 2 corners
        res = ((time**3) - ((time-c[0])**3) - ((time-c[1])**3)) / f1 / f2 / f3 / 6

    else: # 3 corners
        res = ((time**3) - ((time-c[0])**3) - ((time-c[1])**3) - ((time-c[2])**3)) / f1 / f2 / f3 / 6.0

    if flip: res = 1.0 - res

print(min(1.0, max(0.0, res)))

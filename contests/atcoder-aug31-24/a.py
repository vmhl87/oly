[a, b] = [int(x) for x in input().split()]

ans = 2

if (a+b) % 2 == 0: ans = 3
if a == b: ans = 1

print(ans)

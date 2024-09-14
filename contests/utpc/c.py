n = int(input())

s = input()

diff = 0

for i in range(len(s)-1):
    if s[i] != s[i+1]: diff += 1

print((diff+1)//2)

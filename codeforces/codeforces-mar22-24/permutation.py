M = 1000000007
P = 1000000005

def fact(x):
    ret = 1
    for i in range(2, x+1):
        ret = (ret*i) % M
    return ret

def inv(x):
    ret = 1
    p = P
    while p > 0:
        if p % 2 == 1:
            ret = (ret*x) % M
        x = (x*x) % M
        p = p // 2
    return ret

def nck(n, k):
    num = fact(n)
    den = (fact(k)*fact(n-k)) % M
    return (num*inv(den)) % M

def test_case():
    [n,p,s] = [int(x) for x in input().split()]
    ps = [int(x) for x in input().split()]
    ss = [int(x) for x in input().split()]

    if ps[-1] != ss[0] or ps[0] != 1 or ss[-1] != n:
        print(0)
        return

    ret = nck(n-1, ss[0]-1)

    for i in range(1, p):
        diff = ps[i] - ps[i-1] - 1
        if diff > 0:
            ret = (ret*nck(ps[i]-2, diff)) % M
            ret = (ret*fact(diff)) % M

    for i in range(1, s):
        diff = ss[i] - ss[i-1] - 1
        if diff > 0:
            ret = (ret*nck(n-ss[i-1]-1, diff)) % M
            ret = (ret*fact(diff)) % M

    print(ret)

t = int(input())

for i in range(t):
    test_case()

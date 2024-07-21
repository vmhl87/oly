def fibonacci(n):
    pre, transform = [0, 1], [[0, 1], [1, 1]]

    while n:  # binary exponentiation!
        if n % 2: pre = vmul(pre, transform)
        transform = mmul(transform, transform)
        n //= 2

    return pre[0]

def mmul(m1, m2):  # multiply matrix by matrix
    ret = [[0, 0], [0, 0]]

    for i in range(2):
        for j in range(2):
            for k in range(2):
                ret[i][j] = (ret[i][j] + m1[i][k]*m2[k][j]) % M

    return ret

def vmul(v, m):  # multiply vector by matrix
    ret = [
        m[0][0]*v[0] + m[0][1]*v[1],
        m[1][0]*v[0] + m[1][1]*v[1]
    ]

    return [i % M for i in ret]

M = 1000000007

i = int(input())

print(fibonacci(i))

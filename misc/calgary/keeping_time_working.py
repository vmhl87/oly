def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def minv(a, b):
    tmp = b
    y, x = 0, 1

    if b == 1:
        return 0

    while a > 1:
        q = a // b
        t = b

        b = a % b
        a = t
        t = y

        y = x - q * y
        x = t

    if x < 0:
        x += tmp

    return x

def main():
    n, a, b = map(int, input().split())

    g = gcd(a, b)
    if n % g == 0:
        n //= g
        a //= g
        b //= g
    else:
        print(-1)
        return

    val1 = (((n % b) * minv(a, b)) % b) * a
    val2 = (((n % a) * minv(b, a)) % a) * b
    val = min(val1, val2)

    if val < n:
        val += n

    print(val * g)

if __name__ == "__main__":
    main()

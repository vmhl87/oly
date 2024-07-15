class segtree:
    def __init__(self, n):
        if type(n) == list: self._len = len(n)
        else: self._len = n

        self._tree = [0 for _ in range(self._len)]

        if type(n) == list: self._tree += n
        else: self._tree += self._tree

        i = self._len - 1
        while i:
            self._tree[i] = self._tree[i*2] + self._tree[i*2+1]
            i -= 1

    def add(self, i, v):
        i += self._len

        while i:
            self._tree[i] += v
            i //= 2

    def range(self, l, r):
        l += self._len
        r += self._len + 1

        res = 0

        while l < r:
            if l & 1:
                res += self._tree[l]
                l += 1

            if r & 1:
                r -= 1
                res += self._tree[r]

            l //= 2
            r //= 2

        return res

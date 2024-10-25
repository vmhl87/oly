class treeset:
    def __init__(self, items=None):
        self._size = 0
        self._tree = None

        if items != None:
            for item in items:
                self.add(item)

    def __len__(self):
        return self._size

    class node:
        def __init__(self, val):
            self.d = val
            self.p = None
            self.l = None
            self.r = None
            self.h = 0

        def lsz(self):
            if self.l == None:
                return 0
            return self.l.h

        def rsz(self):
            if self.r == None:
                return 0
            return self.r.h

        def bal(self):
            return self.lsz() - self.rsz()
        
        def upd(self):
            a, b = self.lsz(), self.rsz()
            if a > b:
                self.h = 1 + a
            else:
                self.h = 1 + b

        def setl(self, node):
            self.l = node
            if node != None:
                node.p = self
            self.upd()

        def setr(self, node):
            self.r = node
            if node != None:
                node.p = self
            self.upd()

        def lch(self):
            return self.p != None and self.p.l == self

        def rch(self):
            return self.p != None and self.p.r == self

        def rotl(self):
            temp = self.r
            self.setr(temp.l)
            temp.setl(self)
            return temp

        def rotr(self):
            temp = self.l
            self.setl(temp.r)
            temp.setr(self)
            return temp

        def begin(self):
            prev, curr = None, self
            while curr != None:
                prev = curr
                curr = curr.l
            return prev
    
        def end(self):
            prev, curr = None, self
            while curr != None:
                prev = curr
                curr = curr.r
            return prev

        def left(self):
            if self.l != None:
                return self.l.end()

            res = self
            while res.p != None:
                if res.p.l != res:
                    return res.p
                res = res.p

            return None

        def right(self):
            if self.r != None:
                return self.r.begin()

            res = self
            while res.p != None:
                if res.p.r != res:
                    return res.p
                res = res.p

            return None

        def fmt(self):
            res = ""
            if self.l != None:
                res += self.l.fmt()
                res += ' '
            res += str(self.d)
            if self.r != None:
                res += ' '
                res += self.r.fmt()
            return res

    def _rebal(self, node):
        if node == None:
            return None

        bal = node.bal()

        if bal == 2:
            if node.l.bal() == -1:
                node.setl(node.l.rotl())
            return node.rotr()

        elif bal == -2:
            if node.r.bal() == 1:
                node.setr(node.r.rotr())
            return node.rotl()

        return node

    def _begin(self):
        if self._tree == None:
            return None
        return self._tree.begin()

    def _end(self):
        if self._tree == None:
            return None
        return self._tree.end()

    def _fix(self, node):
        while node != None:
            node.setl(self._rebal(node.l))
            node.setr(self._rebal(node.r))
            node.upd()
            node = node.p
        self._tree = self._rebal(self._tree)
        if self._tree != None:
            self._tree.p = None

    def __str__(self):
        return f"({self._tree.fmt() if self._tree != None else ''})"

    def multiadd(self, val):
        self._size += 1

        p, curr = None, self._tree
        while curr != None:
            p = curr
            if val < curr.d:
                curr = curr.l
            else:
                curr = curr.r

        new = self.node(val)

        new.p = p
        if p == None:
            self._tree = new
        elif val < p.d:
            p.l = new
        else:
            p.r = new

        self._fix(new)

    def _find(self, val):
        p = self._tree
        while p != None:
            if val == p.d:
                return p
            if val < p.d:
                p = p.l
            else:
                p = p.r
        return None

    def add(self, val):
        if self._find(val) == None:
            self.multiadd(val)

    def _leaf(self, node):
        if node.p == None:
            self._tree = None
        elif node.lch():
            node.p.l = None
        else:
            node.p.r = None
        if node.p != None:
            self._fix(node.p)

    def _erase(self, node):
        if node == None:
            return

        self._size -= 1

        rep = None
        if node.l != None:
            rep = node.l.end()
            if rep.lch():
                rep.p.setl(None)
            else:
                rep.p.setr(None)

        elif node.r != None:
            rep = node.r.begin()
            if rep.lch():
                rep.p.setl(None)
            else:
                rep.p.setr(None)

        if rep == None:
            self._leaf(node)

        else:
            node.d = rep.d
            self._fix(rep.p)

    def erase(self, val):
        self._erase(self._find(val))

    def __contains__(self, val):
        return self._find(val) != None

    def __iadd__(self, val):
        self.add(val)
        return self

    def __isub__(self, val):
        self.erase(val)
        return self

    class iterator:
        def __init__(self, node):
            self.node = node
    
        def end(self):
            return self.node == None

        def __str__(self):
            return str(self())

        def __call__(self):
            if self.node == None:
                return None
            return self.node.d

        def __iadd__(self, steps):
            if steps < 0:
                return self.__isub__(-steps)
            for _ in range(steps):
                if self.node != None:
                    self.node = self.node.right()
                else: break
            return self

        def __isub__(self, steps):
            if steps < 0:
                return self.__iadd__(-steps)
            for _ in range(steps):
                if self.node != None:
                    self.node = self.node.left()
                else: break
            return self

        def __next__(self):
            if self.node != None:
                res = self.node.d
                self.__iadd__(1)
                return res
            else:
                raise StopIteration

    def find(self, val):
        node = self._find(val)
        if node == None:
            return None
        return self.iterator(node)

    def __iter__(self):
        node = self._begin()
        return self.iterator(node)

    def begin(self):
        node = self._begin()
        return self.iterator(node)

    def end(self):
        node = self._end()
        return self.iterator(node)



def intersection(L1, L2):
    pass

def set_to_int(X):
    res = 0
    m = max(X)
    p = 1
    for i in range(1, m + 1):
        if i in X:
            res += p
        p *= 2
    return res

def code_to_set(c):
    res = []
    i = 1
    p = 1
    while c != 0:
        if (c % (2 * p)) == p:
            res.append(i)
            c -= p
        i += 1
        p *= 2
    return res

class QuasiShuffle:

    def __init__(self, k, l):
        self.k = k
        self.l = l
        # Preimage of 1: L = for {1}, R for {k + 1} and B for {1, k + 1}
        if l == 0 and k == 0:
            self.pre = None
        elif l == 0:
            self.pre = 'L'
            self.sub = QuasiShuffle(k - 1, 0)
        elif k == 0:
            self.pre = 'R'
            self.sub = QuasiShuffle(0, l - 1)
        else:
            self.pre = 'L'
            self.sub = QuasiShuffle(k - 1, l)

    def image(self):
        if self.pre == None:
            return []
        S = [s + 1 for s in self.sub.image()]
        if self.pre == 'L':
            return [1] + S
        elif self.pre == 'R':
            return S[:self.k] + [1] + S[self.k:]
        else:
            return [1] + S[:self.k - 1] + [1] + S[self.k - 1:]
                      
    def __repr__(self):
        return repr(self.image())

    def next(self):
        if self.pre != None:
            ret = self.sub.next()
            if ret:
                return True
        if self.pre == 'L':
            if self.l == 0:
                return False
            self.pre = 'B'
            self.sub = QuasiShuffle(self.k - 1, self.l - 1)
            return True
        elif self.pre == 'B':
            self.pre = 'R'
            self.sub = QuasiShuffle(self.k, self.l - 1)
            return True
        return False
    
class Tree:

    def __init__(self, c):
        self.c = list(map(set, c))
        self.h = len(c) - 1
        self.n = len(c[-1])

    def __repr__(self):
        return repr(self.c)

    def get_forest(self, amin, amax, i):
        A = set(range(amin, amax + 1))
        c = []
        h = -1
        for j in range(i, self.h + 1):
            X = A.intersection(self.c[j])
            X = set([x - amin + 1 for x in X])
            if h == -1 or X != c[h]:
                h += 1
                c.append(X)
        return Tree(c)

    def left_comb_decomposition(self):
        L = []
        A = set(range(1, self.n + 1))
        for i in range(1, self.h + 1):
            X = A.intersection(self.c[i])
            if len(X) > 0:
                F = self.get_forest(min(X) + 1, max(A), i)
                L = [F] + L
                A = set(range(1, min(X)))
        return L

    def right_comb_decomposition(self):
        R = []
        A = set(range(1, self.n + 1))
        for i in range(1, self.h + 1):
            X = A.intersection(self.c[i])
            if len(X) > 0:
                F = self.get_forest(min(A), max(X) - 1, i)
                R = R + [F]
                A = set(range(max(X) + 1, self.n + 1))
        return R
    
    def code(self):
        return [set_to_int(self.c[i]) for i in range(self.h, 0, -1)]

def tree_from_code(C):
    s = []
    s.append(set([]))
    for i in range(len(C) - 1, -1, -1):
        s.append(code_to_set(C[i]))
    return Tree(s)
        
def atomic_product(T, S, qs):
    R = T.right_comb_decomposition()
    L = S.left_comb_decomposition()
    k = len(R)
    l = len(L)
    r = max(qs)
    print("R = ", R)
    print("L = ", L)
    

    
T1 = Tree([[], [4,6], [4,5,6], [1,4,5,6], [1,2,3,4,5,6]])

T2 = Tree([[], [2], [2,4,5], [2,3,4,5], [1,2,3,4,5]])

T = tree_from_code([511, 510,  494, 302, 14, 2])

sigma = QuasiShuffle(2, 2)
while True:
    print(sigma)
    if not sigma.next():
        break
atomic_product(T2, T1, [1,2,3,4])

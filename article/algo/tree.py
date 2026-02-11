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
        c.append(set([]))
        h = 0
        for j in range(i, self.h + 1):
            X = A.intersection(self.c[j])
            X = set([x - amin + 1 for x in X])
            if X != c[h]:
                h += 1
                c.append(X)
        return Tree(c)


    def left_comb_decomposition(self):
        R = []
        A = set(range(1, self.n + 1))
        for i in range(1, self.h + 1):
            X = A.intersection(self.c[i])
            if len(X) > 0:
                F = self.get_forest(min(X) + 1, max(A), i)
                R = R + [F]
                A = set(range(1, min(X)))
        return R

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
        
    

    
T1 = Tree([[], [4,6], [4,5,6], [1,4,5,6], [1,2,3,4,5,6]])
T2 = Tree([[], [2], [2,4,5], [2,3,4,5], [1,2,3,4,5]])

T = tree_from_code([511, 510,  494, 302, 14, 2])

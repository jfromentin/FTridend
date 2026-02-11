def intersection(L1, L2):
    pass

class Tree:

    def __init__(self, c):
        self.c = list(map(set, c))
        self.h = len(c) - 1
        self.n = len(c[-1])

    def __repr__(self):
        return repr(self.c)

    def left_forest(self, amin, amax, i):
        A = set(range(amin, amax + 1))
        c = []
        c.append(set([]))
        h = 0
        for j in range(i, self.h + 1):
            X = A.intersection(self.c[j])
            X = set([a - amin for a in X])
            if X != c[h]:
                h += 1
                c.append(X)
        return Tree(c)


    def left_comb_decomposition(self):
        R = []
        A = set(range(1, self.n + 1))
        for i in range(1, self.h):
            X = A.intersection(self.c[i])
            if len(X) > 0:
                F = self.left_forest(min(X) + 1, max(A), i)
                R = R + [F]
                A = set(range(1, min(X)))
        return R

T = Tree([[],[4,6], [4,5,6], [1,4,5,6], [1,2,3,4,5,6]])
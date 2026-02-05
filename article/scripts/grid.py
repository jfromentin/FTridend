from math import *

def to_bits(c, na):
    res = []
    f = 1
    for i in range(na):
        if (c & f) == f:
            res.append(1)
        else:
            res.append(0)
        f = f * 2
    return res


def grid(T):
    dx = 1
    dy = 1
    na = int(log2(T[0] + 1))
    h = len(T)
    print("\\begin{tikzpicture}[x=1em,y=1em]")
    for l in range(h):
        c = T[l]
        v = to_bits(c, na)
        for i in range(na):
            if v[i] == 1:
                print("\\filldraw [fill=lightgray] (" + repr(i * dx) + "," + repr((h - l - 1) * dy) + ") rectangle ++ ("  +repr(dx) + "," + repr(dy) + ");") 
    for l in range(h + 1):
        print("\\draw [line width = 1] (0," + repr(l * dy) + ") -- ++ (" + repr(na * dx) + ", 0);")
    for i in range(na + 1):
        print("\\draw [line width = 1] (" + repr(i * dx) + ",0) -- ++ (0, " + repr(l * dy) + ");")
    print("\\end{tikzpicture}");
    
T = [3]
grid(T)

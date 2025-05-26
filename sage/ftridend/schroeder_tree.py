import ftridend.kernel

class ForestInfo:
    def __init__(self):
        self.angle = None
        self.height = None
        self.leaves = None

    def __repr__(self):
        return repr([self.angle, self.height, self.leaves])
    
class SchroederTree:
    def __init__(self, args):
        self.cpp = ftridend.kernel.SchroederTree(args)

    def height(self):
        return self.cpp.height()

    def leaves(self):
        return self.cpp.leaves()

    def layer(self, i):
        return self.cpp.layer(i)

    def __repr__(self):
        return self.cpp.display()

    def left_forests_length(self):
        return self.cpp.left_forests_length()

    def right_forests_length(self):
        return self.cpp.right_forests_length()

    def left_forests(self):
        return self.cpp.left_forests()

    def right_forests(self):
        return self.cpp.right_forests()

import ftridend.kernel

class SchroederTree:
    def __init__(self, args):
        self.cpp = ftridend.kernel.SchroederTree(args)

    def height(self):
        return self.cpp.height()

    def leaves(self):
        return self.cpp.leaves()

    def layer(self, i):
        return self.cpp.layer(i)

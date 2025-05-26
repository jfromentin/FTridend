import ftridend.kernel

    
class SchroederForest:
    def __init__(self, args = None):
        if args != None:
            self.cpp = ftridend.kernel.SchroederForest(args.cpp)
        else:
            self.cpp = ftridend.kernel.SchroederForest()
            
    def size(self):
        return self.cpp.size()

    def height(self):
        return self.cpp.height()

    def leaves(self):
        return self.cpp.leaves()

    def layer(self, i):
        return self.cpp.layer(i)

    def __repr__(self):
        return self.cpp.display()

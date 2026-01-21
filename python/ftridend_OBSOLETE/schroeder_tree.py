import ftridend.kernel
from ftridend.schroeder_forest import *

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
        '''
        Ma super doc
        Example : gfjshgfd
        '''
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

    def left_forest(self, i):
        res = SchroederForest()
        self.cpp.left_forest(res.cpp, i)
        return res

    def right_forest(self, i):
        res = SchroederForest()
        self.cpp.right_forest(res.cpp, i)
        return res
    
    def left_forest_info(self, i):
        temp = self.cpp.left_forest_info(i)
        res = ForestInfo()
        res.height = temp[0]
        res.leaves = temp[1]
        res.angle = temp[2]
        return res
    
    def right_forest_info(self, i):
        temp = self.cpp.right_forest_info(i)
        res = ForestInfo()
        res.height = temp[0]
        res.leaves = temp[1]
        res.angle = temp[2]
        return res
    

#****************************************************************************#
#    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     #
#                                                                            #
#  This file is part of FTridend <https://github.com/jfromentin/FTridend>    #
#                                                                            #
#  FTridend is a free software: you can redistribute it and/or modify it     #
#  under the terms of the GNU General Public License as published by the     #
#  Free Software Foundation, either version 3 of the License, or (at your    #
#  option) any later version.                                                #
#                                                                            #
#  FTridend is distributed in the hope that it will be useful, but WITHOUT   #
#  ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or    #
#  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  #
#  more details.                                                             #
#                                                                            #
#  You should have received a copy of the GNU General Public License along   #
#  with FTridend. If not, see <https://www.gnu.org/licenses/>.               #
#****************************************************************************#

import os
from distutils.core import setup, Extension
from sage.env import *

#SAGE_EXT = os.path.join(SAGE_SRC, 'sage', 'ext')
#SAGE_INC = os.path.join(SAGE_SRC, 'c_lib', 'include')
#SAGE_MOD = os.path.join(SAGE_SRC, 'sage')

# the option -Wp,-w remove all preprocessor warnings
module_combo = Extension('ftridend.kernel',
                    extra_compile_args = ['-std=c++20', '-O3', '-g'],
                    include_dirs = [],#SAGE_EXT,SAGE_INC,SAGE_MOD],
                    sources = ['cpp/kernel/schroeder_tree.cpp',
                               #
                               'cpp/sage/schroeder_tree.cpp',
                               #
                               'cpp/sage/module.cpp'])

setup (name = 'ftridend.kernel', ext_modules = [module_combo])

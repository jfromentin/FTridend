//****************************************************************************//
//    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of SchroederTree project:                               //
//              <https://github.com/jfromentin/schroeder_tree>                //
//                                                                            //
//  SchroederTree is a free software: you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by the  //
//  Free Software Foundation, either version 3 of the License, or (at your    //
//  option) any later version.                                                //
//                                                                            //
//  SchroederTree is distributed in the hope that it will be useful, but      //
//  WITHOUT ANY WARRANTY; without even the implied warranty of                //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  //
//  Public License for more details.                                          //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with SchroederTree. If not, see <https://www.gnu.org/licenses/>.          //
//****************************************************************************//

#ifndef SCHROEDER_FOREST_HPP
#define SCHROEDER_FOREST_HPP

#include <bit>
#include "schroeder_tree.hpp"

using namespace std;

class SchroederForest:public SchroederTree{
private:
  int size;
public:
  void compute_size();
  SchroederForest();
  SchroederForest(const SchroederTree& T);
  void display() const;
};

inline SchroederForest::SchroederForest(){
}

inline SchroederForest::SchroederForest(const SchroederTree& T): SchroederTree(T) {
  compute_size(); 
}

inline void SchroederForest::compute_size() {
  size = n - popcount(p[h - 1]);
}
#endif

//****************************************************************************//
//    Copyright (C) 2026 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                       Pierre Catoire <catoire_research@proton.me>          //
//                                                                            //
//  This file is part of FTridend <https://github.com/jfromentin/FTridend>    //
//                                                                            //
//  FTridend is free software: you can redistribute it and/or modify it       //
//  under ethe terms of the GNU General Public License as published by the    //
//  Free Software Foundation, either version 3 of the License, or             //
//  (at your option) any later version.                                       //
//                                                                            //
//  FTridend is distributed in the hope that it will be useful, but WITHOUT   //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License      //
//  for more details.                                                         //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with FTridend. If not, see <https://www.gnu.org/licenses/>.               //
//****************************************************************************//

#ifndef SCHROEDER_FOREST_HPP
#define SCHROEDER_FOREST_HPP

#include <bit>
#include "schroeder_tree.hpp"

using namespace std;

class SchroederForest:public SchroederTree{
  friend SchroederTree;
private:
  int s;
protected:
  void compute_size();
public:
  SchroederForest();
  SchroederForest(const SchroederTree& T);
  void display(ostream& os = cout) const;
  Int size() const;
};

inline
SchroederForest::SchroederForest(){
}

inline
SchroederForest::SchroederForest(const SchroederTree& T): SchroederTree(T) {
  compute_size(); 
}

inline void
SchroederForest::compute_size() {
  s = popcount(p[h - 1]);
}

inline Int
SchroederForest::size() const {
  return s;
}

#endif

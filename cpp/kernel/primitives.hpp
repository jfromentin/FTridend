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

#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <unordered_set>
#include <fstream>
#include "schroeder_module.hpp"

using namespace std;


class Primitives{
public:
  unordered_set<SchroederVector<int>> co_dendriform[N];
  unordered_set<SchroederVector<int>> co_associative[N];
  size_t n;
  unordered_set<SchroederVector<int>>::const_iterator tuple[N];
  SchroederVector<int> theta(const SchroederVector<int>&);
  SchroederVector<int> omega(int l,fstream& file);
  SchroederVector<int> omega_left(int first, int last); //
  SchroederVector<int> omega_right_middle(int first, int last); 
public:
  Primitives();
  void init();
  int rank() const;
  int size_co_associative(int i) const;
  int size_co_dendriform(int i) const;
  void display_co_dendriform(int i) const;
  void display_co_associative(int i) const;
  void next(fstream& file);
};

void to_matrix(const unordered_set<SchroederVector<int>>& F);

inline Primitives::Primitives() {
  n = 0;
  for (int i = 0; i < (int)N; ++ i) {
    co_dendriform[i].clear();
    co_associative[i].clear();
  }
}

inline int
Primitives::rank() const {
  return n;
}

inline int
Primitives::size_co_associative(int i) const {
  assert(0 <= i and i < (int)N);
  return co_associative[i].size();
}

inline int
Primitives::size_co_dendriform(int i) const {
  assert(0 <= i and i < (int)N);
  return co_dendriform[i].size();
}

#endif

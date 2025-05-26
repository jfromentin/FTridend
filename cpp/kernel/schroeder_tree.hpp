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

#ifndef SCHROEDER_TREE_HPP
#define SCHROEDER_TREE_HPP

#include <bit>
#include <initializer_list>
#include "common.hpp"
#include "array.hpp"

class SchroederForest;

struct ForestInfo{
  Int h;
  Int n;
  Int a; // angle
};

class SchroederTree{
protected:
  Int n; // Number of leaves
  Int h; // Height of the tree
  Int p[N]; // Chain partition giving the structure of the tree
  int number_left_forests;
  int number_right_forests;
  ForestInfo left_forest_infos[N];
  ForestInfo right_forest_infos[N];
  void compute_left_forest_infos();
  void compute_right_forest_infos();
public:
  SchroederTree();
  SchroederTree(const initializer_list<Int>& l);
  bool validate();
  void initialize();

  Int height() const;
  Int leaves() const;
  Int layer(Int i) const;
  Int left_forests_length() const;
  Int right_forests_length() const;
    
  Array<SchroederForest> left_comb_splitting() const;
  Array<SchroederForest> right_comb_splitting() const;
  
  void display(ostream& os = cout) const;
  
  // Sage functions
  void sage_init(Int h, Int n);
  void sage_set_value(Int i, Int v);
};


inline
SchroederTree::SchroederTree() {
  n = 0;
  h = 0;
  number_left_forests = 0;
  number_right_forests = 0;
}

inline void
SchroederTree::sage_init(Int hh, Int nn) {
  h = hh;
  n = nn;
}

inline void
SchroederTree::sage_set_value(Int i, Int v) {
  assert(i < h - 1);
  p[i] = v;
}

inline void
SchroederTree::initialize() {
  compute_left_forest_infos();
  compute_right_forest_infos();
}

inline Int
SchroederTree::height() const {
  return h;
}

inline Int
SchroederTree::leaves() const {
  return n;
}

inline Int
SchroederTree::left_forests_length() const {
  return number_left_forests;
}

inline Int
SchroederTree::right_forests_length() const {
  return number_right_forests;
}

inline Int
SchroederTree::layer(Int i) const {
  assert(0<= i and i < h);
  return p[i];
}


#endif

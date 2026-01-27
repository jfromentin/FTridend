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

#ifndef SCHROEDER_TREE_HPP
#define SCHROEDER_TREE_HPP

#include <bit>
#include <initializer_list>

#include "common.hpp"
#include "array.hpp"
#include "quasi_shuffle.hpp"
#include "packed_word.hpp"

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
  SchroederTree(const SchroederTree&, const SchroederTree&, const QuasiShuffle &sigma);
  bool validate();
  void initialize();

  Int height() const;
  Int leaves() const;
  Int layer(Int i) const;
  Int left_forests_length() const;
  Int right_forests_length() const;
  const ForestInfo& get_left_forest_info(Int i) const;
  const ForestInfo& get_right_forest_info(Int i) const;
  void set_left_comb_forest(SchroederForest& f, Int i) const;
  void set_right_comb_forest(SchroederForest& f, Int i) const;
  Array<SchroederForest> left_comb_splitting() const;
  Array<SchroederForest> right_comb_splitting() const;

  void display(ostream& os = cout) const;

  string to_latex() const;
  
  // Sage functions
  void sage_init(Int h, Int n);
  void sage_set_value(Int i, Int v);

  //
  size_t hash() const;
  bool operator==(const SchroederTree&) const;
  PackedWord packed_word() const;
};

//***********************
//* Auxiliary functions *
//***********************

string to_string(const SchroederTree& T);

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
  assert (0 <= i and i < h);
  return p[i];
}

inline const ForestInfo&
SchroederTree::get_left_forest_info(Int i) const {
  assert (0 <= i and i < number_left_forests);
  return left_forest_infos[i];
}

inline const ForestInfo&
SchroederTree::get_right_forest_info(Int i) const {
  assert (0 <= i and i < number_right_forests);
  return right_forest_infos[i];
}

inline size_t
SchroederTree::hash() const {
  size_t res = 0;
  for (int i = 0; i < h - 1; ++ i) res += p[i];
  return res;		    			     
}

inline bool
SchroederTree::operator==(const SchroederTree& t) const {
  if (h != t.h) return false;
  for (int i = 0; i < h - 1; ++ i) {
    if (p[i] != t.p[i]) return false;
  }
  return true;
}
#endif

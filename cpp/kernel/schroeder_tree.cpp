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

#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

bool SchroederTree::validate() {
  if (p[0] != ((1L << (n - 1)) - 1)) return false;
  if (p[h - 1] != 0) return false;
  Int prev = p[0];
  for (int i = 1; i < h - 1; ++ i) {
    Int v = p[i];
    if ((v | prev) != prev) return false;
    prev = v;
  }
  return true;
}
SchroederTree::SchroederTree(const initializer_list<Int>& l) {
  h = l.size() + 1;
  auto it = l.begin(); 
  Int v = *it;
  n = popcount(v) + 1;
  p[0] = v;
  int k = 0;
  for (++ it; it != l.end(); ++ it) {
    v = *it;
    p[++ k] = v;
  }
  p[h - 1] = 0;
  assert(validate());
  initialize();
}

void SchroederTree::display(ostream& os) const {
  for (int j = 0; j < n; ++ j) {
    os << char('a' + j) << ' ';
  }
  if (verbose_display) {
    os << "  ";
    for (int j = 0; j < n - 1; ++ j) {
      os << char('0' + j);
    }
  }
  os << endl;
  for (int i = 1; i < h ; ++ i) {
    bool line = false;
    Int f = 1;
    for (int j = 0; j < n - 1; ++ j) {
      if (p[i - 1] & f) {
	if (line) {
	  if (not (p[i] & f)) {
	    os << "\u2534";
	  }
	  else {
	    os << "\u2524";
	  }
	}
        else if ((p[i] & f) == f) os << "\u2502"; //|
	else os << "\u2570"; //|_
      }
      else if (line) os << "\u2500"; //-
      else os << ' ';
      if (not (p[i] & f)) {
	if ((p[i - 1] & f)) line = true;
      }
      else line = false;
      if (line) os << "\u2500"; //-
      else os << ' ';
      
      f *= 2;
    }
    if (line) os << "\u2524"; //-|
    else os << "\u2502"; //|
    if (verbose_display) {
      os << " = ";
      f = 1;
      for (int j = 0; j < n - 1; ++ j) {
	if (p[i] & f) os << '*';
	else os << '.';
	f *= 2;
      }
      os << " = " << p[i];
    }
    os << endl;
  }
  if (display_root) {
    // Display root
    for (int j = 0; j < n - 1; ++ j) {
      os << "  ";
    }
    os << "\u2567" << endl;
  }
}

void SchroederTree::compute_left_forest_infos() {
  number_left_forests = 0;
  // Test empty case
  if (h < 2) return;
  // We start with the rightmost angle
  Int mask = p[0]; 
  Int a = n - 1;
  for (int l = h - 2 ; l >= 0; -- l){
    Int temp = mask & p[l];
    if (temp != 0) {
      int t = countr_zero(temp);
      ForestInfo& node = left_forest_infos[number_left_forests++];
      node.a = t;
      node.h = l + 1;
      node.n = a - t;
      a = t;
      mask = (1L << t) - 1;
    }
  }
}

void SchroederTree::compute_right_forest_infos() {
  number_right_forests = 0;
  // Test empty case
  if (h < 2) return;
  Int mask = p[0];
  // We start with the left tmost angle
  Int a = -1;
  for (int l = h - 2 ; l >= 0; -- l){
    Int temp = mask & p[l];
    if (temp != 0) {
      int t = 15 - countl_zero(temp);
      ForestInfo& node = right_forest_infos[number_right_forests++];
      node.a = t;
      node.h = l + 1;
      node.n = t - a;
      a = t;
      mask &= ~((1L << (a + 1)) -1);
    }
  }
}

Array<SchroederForest> SchroederTree::left_comb_splitting() const {
  Array<SchroederForest> res(number_left_forests);
  for (int f = 0; f < number_left_forests; ++f) {
    const ForestInfo& info = left_forest_infos[f];
    res[f].h = info.h;
    res[f].n = info.n;
    Int a2 = (2 << info.a);
    for (int l = 0; l < res[f].h; ++l) {
      res[f].p[l] = p[l] / a2;
    }
    res[f].compute_size();
  }
  return res;
}

Array<SchroederForest> SchroederTree::right_comb_splitting() const {
  Array<SchroederForest> res(number_right_forests);
  for (int f = 0; f < number_right_forests; ++f) {
    const ForestInfo& info = right_forest_infos[f];
    res[f].h = info.h;
    res[f].n = info.n;
    Int div = (1L << (info.a + 1 - info.n)); 
    for (int l = 0; l < res[f].h; ++l) {
      res[f].p[l] = ((p[l] / div) % (1L << res[f].n));
    }
    res[f].compute_size();
  }
  return res;
}


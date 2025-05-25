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

void SchroederTree::display() const {
  for (int j = 0; j < n; ++ j) {
    cout  << char('a' + j) << ' ';
  }
  if (verbose_display) {
    cout << "  ";
    for (int j = 0; j < n - 1; ++ j) {
      cout  << char('0' + j);
    }
  }
  cout << endl;
  for (int i = 1; i < h ; ++ i) {
    bool line = false;
    Int f = 1;
    for (int j = 0; j < n - 1; ++ j) {
      if (p[i - 1] & f) {
	if (line) {
	  if (not (p[i] & f)) {
	    cout << "\u2534";
	  }
	  else {
	    cout << "\u2524";
	  }
	}
        else if ((p[i] & f) == f) cout << "\u2502"; //|
	else cout << "\u2570"; //|_
      }
      else if (line) cout << "\u2500"; //-
      else cout << ' ';
      if (not (p[i] & f)) {
	if ((p[i - 1] & f)) line = true;
      }
      else line = false;
      if (line) cout << "\u2500"; //-
      else cout << ' ';
      
      f *= 2;
    }
    if (line) cout << "\u2524"; //-|
    else cout << "\u2502"; //|
    if (verbose_display) {
      cout << " = ";
      f = 1;
      for (int j = 0; j < n - 1; ++ j) {
	if (p[i] & f) cout << '*';
	else cout << '.';
	f *= 2;
      }
      cout << " = " << p[i];
    }
    cout << endl;
  }
  if (display_root) {
    // Display root
    for (int j = 0; j < n - 1; ++ j) {
      cout << "  ";
    }
    cout << "\u2567" << endl;
  }
}

void SchroederTree::compute_left_forest_infos() {
  number_left_forests = 0;
  // Test empty case
  if (h < 2) return;
  // We start with the rightmost angle
  Int mask = p[h - 1];
  Int a = n - 1;
  for (int l = h - 2 ; l >= 0; -- l){
    Int temp = mask & p[l];
    if (temp != mask) {
      int t = countr_one(temp);
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
  // We start with the rightmost angle
  Int mask = p[h - 1];
  Int miss_ones = 65535 - mask;
  Int a = -1;
  for (int l = h - 2 ; l >= 0; -- l){
    Int temp = mask & p[l];
    if (temp != mask) {
      temp += miss_ones;
      int t = 15 - countl_one(temp);
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

/*Array<SchroederForest> SchroederTree::left_comb_splitting() const {
  int s = 0; // Size of the comb
  Int pos[N]; // Localisation of each forest of the comb splitting.
  // Forest i will be given as the Schroeder tree of leaves pos[i] + 1, ..., pos[i + 1]
  Int hpos[N]; // Time when pos[i] has been computed
  pos[0] = 0;
  hpos[0] = 0;
  int k = 0;
  Int f = 1;
  for (int i = 0; i < h; ++ i) {
    while (p[i] & f) {
      f *= 2;
      ++ k;
    }
    if (k != pos[s]) {
      ++ s;
      pos[s] = k;
      hpos[s] = i;
    }
  }
  Array<SchroederForest> res(s);
  for (int i = 0; i < s; ++ i) {
    int ind = s - i - 1;
    res[ind].n = pos[i + 1] - pos[i];
    res[ind].h = hpos[i + 1] - hpos[i] + 1;
 
    res[ind].p[0] = 0;
    for (int j = 1; j < res[ind].h; ++ j) {
      res[ind].p[j] = (p[j + hpos[i]] >> (pos[i] + 1));
    }
    res[ind].compute_size();
  }
  return res;
}


Array<SchroederForest> SchroederTree::right_comb_splitting() const {
  int s = 0;
  Int pos[N]; // Localisation of each forest of the comb splitting.
  // Forest i will be given as the Schroeder tree of leaves pos[i + 1], ..., pos[i] - 1
  
  pos[0] = n - 1;

  Int k = n - 1;
  Int f = 1L << (n - 2);
  for (int i = 0; i < h; ++ i) {
    while(p[i] & f) {
      f /= 2;
      --k;
    }
    if (k != pos[s]) {
      ++s;
      pos[s] = k;
    }
  }
 
  Int ht = h - 1;
  Int hb;
  Array<SchroederForest> res(s);
  Int right_leaf  = (1 << (n - 2));
  for (int i = 0; i < s; ++ i) {
    int ind = s - i - 1;
    
    int nf = pos[i] - pos[i + 1];
    res[ind].n = nf;
    // Right most forest is special leave n does not appeat directly 
    //if (i > 0) --nf;
    Int mask = ((1 << (nf - 1)) - 1) << pos[i + 1];
    while((p[ht] & mask) != 0) --ht;
    hb = ht + 1;
    // Detect connection height of the full forest with the right most leaf
    while(((p[hb] & mask) != mask) or ((p[hb] & right_leaf) == 0)) ++hb;
    int hf = hb - ht + 1;
    res[ind].h = hf;
    res[ind].p[0] = 0;
    for (int j = 1; j < hf; ++ j) {
      res[ind].p[j] = ((p[j + ht] & mask) >> pos[i + 1]);
    }
    res[ind].compute_size();
  }
  return res;
  }*/

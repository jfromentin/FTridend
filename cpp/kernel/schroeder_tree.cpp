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
      if (j < 10) os << char('0' + j);
      else os << char('A' + j - 10);
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
  // We start with the left most angle
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

void SchroederTree::set_left_comb_forest(SchroederForest& f, Int i) const {
  assert(0 <= i and i < number_left_forests);
  const ForestInfo& info = left_forest_infos[i];
  f.h = info.h;
  f.n = info.n;
  Int mask = (1L << (f.n - 1)) - 1;
  Int a2 = (2 << info.a);
  for (int l = 0; l < f.h; ++l) {
    f.p[l] = (p[l] / a2) & mask;
  }
  f.compute_size();
}


void SchroederTree::set_right_comb_forest(SchroederForest& f, Int i) const {
  assert(0 <= i and i < number_right_forests);
  const ForestInfo& info = right_forest_infos[i];
  f.h = info.h;
  f.n = info.n;
  Int mask = (1L << (f.n - 1)) - 1;
  Int div = (1L << (info.a + 1 - info.n)); 
  for (int l = 0; l < f.h; ++l) {
    f.p[l] = (((p[l] / div) % (1L << f.n))) & mask;
  }
  f.compute_size();
}

Array<SchroederForest> SchroederTree::left_comb_splitting() const {
  Array<SchroederForest> res(number_left_forests);
  for (int f = 0; f < number_left_forests; ++f) {
    set_left_comb_forest(res[f], f);
  }
  return res;
}

Array<SchroederForest> SchroederTree::right_comb_splitting() const {
  Array<SchroederForest> res(number_right_forests);
  for (int f = 0; f < number_right_forests; ++f) {
    set_right_comb_forest(res[f], f);
  }
  return res;
}

SchroederTree::SchroederTree(const SchroederTree& Tl, const SchroederTree& Tr, const QuasiShuffle &sigma) {
  Int l = Tl.number_right_forests;
  Int r = Tr.number_left_forests;
  // Int t = l + r;
  n = Tl.n + Tr.n - 1;
  h = 0; 
  Int il = 0; // index of the current layer of left tree Tl 
  Int ir; // index of the current layer of right tree Tt 
  // Construction of the forests comming from Tl
  Int shift = Tl.n - 1;
  for(il = 0; il < Tl.h - l; ++ il) {
    p[h] = Tl.p[il] + (Tr.p[0] << shift) ;
    ++ h;   
  }
  // il is a step too far 
  -- il;
  // Read the quasi suffle sigma sigma(0), ..., sigma(t - 1)
  ir = 0;
  Int ifr = r - 1;
  for (int i = sigma.max_value(); i >= 0 ; -- i) {
    GType g = sigma.graft_type(i);
    if (g == GRight or g == GBoth) {
      // Construct a right forest
      const ForestInfo& info = Tr.left_forest_infos[ifr --];
      for (; ir < info.h; ++ ir) {
	p[h] = Tl.p[il] + (Tr.p[ir] << shift) ;
	if (p[h] != p[h - 1]) ++ h; // Check if the new layer is different from the previous one
      }
      if (g == GBoth) ++ il;
      // Graft Right or (Left and Right)
      p[h] = Tl.p[il] + (Tr.p[ir] << shift);
      ++ h;
    }
    else {
      ++ il;
      p[h] = Tl.p[il] + (Tr.p[ir] << shift);
      ++ h;   
    }
  }
  initialize();
}

string SchroederTree::to_latex() const {
  string str = "\\begin{tikzpicture}\n";
  float x[N][N];
  
  for (int i = 0; i < n; ++ i) {
    x[0][i] = i;
  }
  //cout << "h = " << h << endl;
  //cout << "n = " << n << endl;
  for (int y = 0; y < h; ++ y) {
    //cout << "Level " << n - y  << endl;
    int f = 1;
    int left = -1;
    for (int i = 0; i < n; ++ i) x[y + 1][i] = x[y][i];
    for (int i = 0; i < n - 1; ++ i) {
      //cout << i << ": " << f << " -> " << (f & p[y]) << endl;
      if (not (f & p[y])) {
	if (left == -1) left = i;
      }
      else if(left != -1) {
	//cout << "Fusion from " << left << " to " << i  << endl;
	float x_avg = (x[y][left] + x[y][i]) / 2;
	for (int j = left; j <= i; ++ j) x[y + 1][j] = x_avg;
	left = -1;
      }
   
      f *= 2;
    }
    if (left != -1) {
      //cout << "Fusion from " << left << " to " << n  - 1 << endl;
      float x_avg = (x[y][left] + x[y][n - 1]) / 2;
      for (int j = left; j <= n - 1; ++ j) x[y + 1][j] = x_avg;
    }
  }
  /*for (int y = 1; y <= h; ++ y) {
    cout << "y = " << y << " : ";
    for (int i = 0; i < n; ++ i) {
      cout << x[y][i] << '\t';
    }
    cout << endl;
    }*/
  for (int y = 1; y < h; ++ y) {
    //cout << "y = " << y << endl;
    for (int i = 0; i < n; ++ i) {
      str += "\\draw (" + to_string(x[y][i]) + "," + to_string(h - y) + ") -- ("  + to_string(x[y + 1][i]) + "," + to_string(h - y - 1) + "); \n";
      //cout << x[y][i] << '\t';
    }
    //cout << endl;
  }

  str += "\\end{tikzpicture}\n";
  //cout << str << endl;
  return str;
}

//***********************
//* Auxiliary functions *
//***********************

string to_string(const SchroederTree& T) {
  string res = "[";
  for (int i = 0; i < T.height(); ++ i) {
    if (i> 0) res += ", ";
    res += to_string(T.layer(i));
  }
  return res + ']';
}

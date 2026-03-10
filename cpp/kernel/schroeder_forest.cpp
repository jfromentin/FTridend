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

#include "schroeder_forest.hpp"


SchroederForest::SchroederForest(const initializer_list<initializer_list<int>>& l) {
  assert(l.size() > 0);
  h = l.size() - 1;
  c = new BSet[h + 1];
  int i = 0;
  for (auto it = l.begin(); it != l.end(); ++ it) {
    c[i ++] = *it;
  }
  n = c[h].size();  
}

bool SchroederForest::is_well_defined() const {
  for (int l = 0; l < h; ++ l) {
    if (not c[l].is_subset(c[l + 1])) return false;
  }
  if (c[h].max() != n) return false;
  return true;
}


void SchroederForest::display(ostream& os) const {
  for (int j = 0; j <= n; ++ j) {
    os << char('a' + j) << ' ';
  }
  if (verbose_display) {
    os << "  ";
    for (int j = 1; j <= n; ++ j) {
      if (j < 10) os << char('0' + j);
      else os << char('A' + j - 10);
    }
  }
  os << endl;
  for (int j = 0; j <= n; ++ j)  os << "\u2502 ";
  if (verbose_display) {
    os << "= ";
    for (int j = 0; j < n; ++ j) os << "\u2588";
    os << " = " << (BSet_t)c[h];
  }
  os << endl;
  for (int i = 1; i <= h ; ++ i) {
    bool line = false;
    BSet_t f = 1;
    for (int j = 0; j < n; ++ j) {
      if ((BSet_t)c[h - i + 1] & f) {
	if (line) {
	  if (not ((BSet_t)c[h - i] & f)) {
	    os << "\u2534";
	  }
	  else {
	    os << "\u2524";
	  }
	}
        else if (((BSet_t)c[h - i] & f) == f) os << "\u2502"; //|
	else os << "\u2570"; //|_
      }
      else if (line) os << "\u2500"; //-
      else os << ' ';
      if (not ((BSet_t)c[h - i] & f)) {
	if (((BSet_t)c[h - i + 1] & f)) line = true;
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
      for (int j = 0; j < n; ++ j) {
	if ((BSet_t)c[h - i] & f) os << "\u2588";
	else os << "\u2591";
	f *= 2;
      }
      os << " = " << (BSet_t)c[h - i];
    }
    os << endl;
  }
}

string SchroederForest::to_latex() const {
  string str = "\\begin{tikzpicture}\n";
  float x[N][N];
  for (int i = 0; i <= n; ++ i) {
    x[0][i] = i / 4.0;
  }
  for (int y = 0; y <= h; ++ y) {
    int f = 1;
    int left = -1;
    for (int i = 0; i <= n; ++ i) x[y + 1][i] = x[y][i];
    for (int i = 0; i < n; ++ i) {
      if (not (f & (BSet_t)c[h - y])) {
	if (left == -1) left = i;
      }
      else if(left != -1) {
	float x_avg = (x[y][left] + x[y][i]) / 2;
	for (int j = left; j <= i; ++ j) x[y + 1][j] = x_avg;
	left = -1;
      }
   
      f *= 2;
    }
    if (left != -1) {
      float x_avg = (x[y][left] + x[y][n - 1]) / 2;
      for (int j = left; j <= n; ++ j) x[y + 1][j] = x_avg;
    }
  }
    for (int y = 0; y <= h; ++ y) {
    for (int i = 0; i < n; ++ i) {
      str += "\\draw (" + to_string(x[y][i]) + "," + to_string((h - y) / 4.0) + ") -- ("  + to_string(x[y + 1][i]) + "," + to_string((h - y - 1) / 4.0) + "); \n";
    }
  }
  str += "\\end{tikzpicture}\n";
  return str;
  }


/*PackedWord
SchroederTree::packed_word() const {
  Array<int> res(n - 1);
  for (int i = 1; i < h; ++ i) {
    int dead = p[i-1] - p[i];
    while (dead != 0) {
      int dead_angle = __builtin_ctz(dead);
      res[dead_angle] = i;
      dead -= (1 << dead_angle);
    }
  }
  return res;
}

Array<SimpleCut>
SchroederTree::simple_cuts() const {
  //display(cout);
  PackedWord w = packed_word();
  // There is exatclty h - 1 simple cuts
  Array<SimpleCut> res(h - 1);
  for (int i = 1; i < h; ++ i) {
    int dead = p[i - 1] - p[i];
    int dead_angle = __builtin_ctz(dead);
    int left = dead_angle - 1;
    if (left >= 0) {
      while (left >= 0 and w[left] <= i) -- left;
    }
    ++ left;
    int right = dead_angle + 1;
    while (right < n - 1  and w[right] <= i) ++ right;
    -- right;
    res[i - 1].left = left;
    res[i - 1].right = right;
    //cout << i - 1 << " : " << left << " -> " << right << endl;
  }
  return res;
}

void
SchroederTree::set_sub_tree(SchroederTree& t, int left, int right) const {
    int len = right - left + 1;
    int mask = ((1L << len) - 1) << left;
    t.n = len + 1;
    t.h = h;
    for (int l = 0; l <= h; ++l) {
      t.p[l] = (p[l] & mask) >> left;
    }
    t.normalize();
    t.initialize();
}

void
SchroederTree::set_root(SchroederTree& t, const Cut& c, const Array<SimpleCut>& sc) const {
  int s = c.s;
  t.n = n;
  t.h = h;
  int left[N];
  int right[N];

  for (int i = 0; i < s; ++ i) {
    left[i] = sc[c.sc[i]].left;
    right[i] = sc[c.sc[i]].right;
    t.n -= (right[i] - left[i] + 1);
  }
  char temp[N];
  for (int l = 0; l < h; ++ l) {
    Int f = 1;
    for (int j = 0; j < n - 1; ++ j) {
      temp[j] = (p[l] & f) ? '1' : '0';
      f *= 2;
    }
    //for (int j = 0; j < n - 1; ++ j) cout << temp[j] << ' ';
    //cout << " -> ";
    for (int i = 0; i < s; ++ i) {
      for (int k = left[i]; k <= right[i]; ++ k) temp[k] = 'x';
    }
    //for (int j = 0; j < n - 1; ++ j) cout << temp[j] << ' ';
    //cout << endl;
    f = 1;
    Int rp = 0;
    for (int j = 0; j < n - 1; ++ j) {
      if (temp[j] == '1') {
	rp += f;
	f *=2;
      }
      else if (temp[j] == '0') {
	f *= 2;
      }			   
    }
    t.p[l] = rp;
  }
  t.normalize();
  t.initialize();
  //cout << endl;
  //t.display(cout);
}


void SchroederTree::normalize() {
  int prev = p[0];
  int dh = 0;
  for (int l = 1; l < h; ++ l) {
    if (p[l] == prev) ++ dh;
    else {
      p[l - dh] = p[l];
      prev = p[l];
    }
  }
  h -= dh;
  }*/
  
//***********************
//* Auxiliary functions *
//***********************

string to_string(const SchroederForest& F) {
  string res = "[";
  for (int i = 0; i <= F.height(); ++ i) {
    if (i> 0) res += ", ";
    res += to_string(F.layer(i));
  }
  return res + ']';
}

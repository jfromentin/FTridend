//****************************************************************************//
//    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of FTridend <https://github.com/jfromentin/FTridend>    //
//                                                                            //
//  FTridend is a free software: you can redistribute it and/or modify it     //
//  under the terms of the GNU General Public License as published by the     //
//  Free Software Foundation, either version 3 of the License, or (at your    //
//  option) any later version.                                                //
//                                                                            //
//  FTridend is distributed in the hope that it will be useful, but WITHOUT   //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for  //
//  more details.                                                             //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with FTridend. If not, see <https://www.gnu.org/licenses/>.               //
//****************************************************************************//

#ifndef QUASI_SHUFFLE_HPP
#define QUASI_SHUFFLE_HPP

#include "common.hpp"
enum PType {PLeft, PLeftMiddle, PMiddle, PRight, PRightMiddle, PAll};
enum QSType {QSBase, QSLeft, QSMiddle, QSRight};
enum GType {GLeft = 1, GRight = 2, GBoth = 3};

class QuasiShuffle {
private:
  PType p;
  int l, r;
  QSType type;
  QuasiShuffle* tau;
  int tab[N];
  /*int nmin, nmax;
  int n;
  int left;
  int right;
  bool next_right();*/
  void compute_left_sigma();
  void compute_middle_sigma();
  void compute_right_sigma();
  void compute_sigma();
public:
  QuasiShuffle();
  QuasiShuffle(int l, int r, PType ptype = PAll);
  void initialize();
  void display() const;
  bool next();
  int operator[](int i) const;
  GType graft_type(int i) const;
  int max_value() const;
  
};


inline QuasiShuffle::QuasiShuffle() {
  p = PAll;
  l = 0;
  r = 0;
  tau = nullptr;
}

inline QuasiShuffle::QuasiShuffle(int ll, int rr, PType pp) {
  p = pp;
  l = ll;
  r = rr;
  initialize();
}

inline int QuasiShuffle::operator[](int i) const {
  assert(i < l + r);
  return tab[i];
}

inline GType QuasiShuffle::graft_type(int i) const {
  int res = 0;
  int j = 0;
  for(; j < l; ++ j) {
    if (tab[j] == i) {
      res = GLeft;
    }
  }
  for(; j < l + r; ++ j) {
    if (tab[j] == i) {
      res += GRight;
      break;
    }
  }
  return GType(res);

}

inline int QuasiShuffle::max_value() const {
  int res = 0;
  for (int i = 0; i < l + r; ++ i){
    if (tab[i] > res) res = tab[i];
  }
  return res;
}
  
#endif


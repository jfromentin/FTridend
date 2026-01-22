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

#include "quasi_shuffle.hpp"

void QuasiShuffle::display() const {
  for(int i = 0; i < l + r; ++ i) cout << tab[i] + 1 << ' ';
  cout << endl;
}

void QuasiShuffle::initialize() {
  if (l == 0 or r == 0) {
    type = QSBase;
    int n = l + r;
    for (int i = 0; i < n; ++ i) tab[i] = i;
    tau = nullptr;
  }
  else {
    switch(p) {
    case PLeft:
    case PLeftMiddle:
    case PAll:
      type = QSLeft;
      tau = new QuasiShuffle(l - 1, r);
      compute_left_sigma();
      break;
    case PMiddle:
    case PRightMiddle:
      type = QSMiddle;
      tau = new QuasiShuffle(l - 1, r - 1);
      compute_middle_sigma();
      break;
    case PRight:
      type = QSRight;
      tau = new QuasiShuffle(l, r - 1);
      compute_right_sigma();
      break;
    default:
      assert(false);
    }
  }
}

void QuasiShuffle::compute_sigma() {
  switch(type) {
  case QSBase:
    break;
  case QSLeft:
    compute_left_sigma();
    break;
  case QSMiddle:
    compute_middle_sigma();
    break;
  case QSRight:
    compute_right_sigma();
    break;
  default:
    assert(false);
  }
}

void QuasiShuffle::compute_left_sigma() {
  tab[0] = 0;
  int ntau = l + r - 1; // n of tau 
  for (int i = 0; i < ntau; ++ i) {
    tab[i + 1] = tau -> tab[i] + 1;
  }
}

void QuasiShuffle::compute_middle_sigma() {
  tab[0] = 0;
  tab[l] = 0;
  if (l == 1 and r == 1) {
    return;
  }
  int ntau = l + r - 2; // n of tau
  int k = 1;
  for (int i = 0; i < ntau; ++ i) {
    if (k == l) ++k;
    tab[k] = tau -> tab[i] + 1;
    ++ k;
  }
}

void QuasiShuffle::compute_right_sigma() {
  tab[l] = 0;
  int ntau = l + r - 1; // n of tau
  int k = 0;
  for (int i = 0; i < ntau; ++ i) {
    if (k == l) ++k;
    tab[k] = tau->tab[i] + 1;
    ++ k;
  }
}

bool QuasiShuffle::next() {
  if (type == QSBase) return false;
  if (tau -> next()) {
    compute_sigma();
    return true;
  }
  switch(type) {
  case QSLeft:
    if (p == PLeft) return false;
    type = QSMiddle;
    delete tau;
    tau = new QuasiShuffle(l - 1, r - 1);
    compute_middle_sigma();
    return true;
    break;
  case QSMiddle:
    if (p == PMiddle or p == PLeftMiddle) return false;
    type = QSRight;
    delete tau;
    tau = new QuasiShuffle(l, r - 1);
    compute_right_sigma();
    return true;
    break;
  default:
    return false;
  }
}


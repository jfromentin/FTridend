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

#include "ordered_partition.hpp"

ostream& operator<<(ostream& os, const OrderedPartition& P){
  os << '{' << P[0];
  for (int i = 1; i < P.length(); ++ i) {
    os << ',' << P[i];
  }
  return os << '}';
}


bool
OrderedPartition::next() {
  for (int i = l - 1; i > -1; -- i) {
    if (a[i] > 1) {
      -- a[i];
      int m = 0;
      for (int j = 0; j <= i; ++ j) m += a[j];
      int r = n - m;
      l = i + 2;
      a[i + 1] = r;
      for (int j = i + 2; j < (int)N; ++ j) a[j] = 0; 
      return true;
    }
  }
  return false;
}


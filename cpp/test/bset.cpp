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

#include "bset.hpp"

int test_BSet() {
  BSet empty;
  test_equal(to_string(empty), "{}");
  test_equal(empty.is_empty(), true);
  test_equal(empty.size(), 0);
  test_equal(empty.max(), -1);
  BSet S1 = 19;
  test_equal(to_string(S1), "{1, 2, 5}");
  test_equal(S1.is_empty(), false);
  test_equal(S1.size(), 3);
  test_equal(S1.min(), 1);
  test_equal(S1.max(), 5);
  BSet S2 = {5, 7, 10, 14, 3, 14};
  test_equal(to_string(S2), "{3, 5, 7, 10, 14}");
  test_equal(S2.is_empty(), false);
  test_equal(S2.size(), 5);
  test_equal(S2.min(), 3);
  test_equal(S2.max(), 14);
  BSet S3 = S1.intersection(S2);
  test_equal(to_string(S3), "{5}");
  S3 = BSet::range(4, 10);
  test_equal(to_string(S3), "{4, 5, 6, 7, 8, 9, 10}");
  test_equal(to_string(S3.intersection(S2)), "{5, 7, 10}");
  BSet S4 = BSet::range(5);
  test_equal(to_string(S4), "{1, 2, 3, 4, 5}");
  test_equal(to_string(S2.shift(3)), "{6, 8, 10, 13, 17}");
  test_equal(to_string(S2.shift(-2)), "{1, 3, 5, 8, 12}");
  return 0;
}

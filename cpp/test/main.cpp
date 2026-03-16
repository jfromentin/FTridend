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

#include <iostream>
#include "bset.hpp"
#include "schroeder_forest.hpp"

using namespace std;

int main() {
  cout << "\u250C";
  for (int i = 0; i < 24; ++i) cout << "\u2500";
  cout << "\u2510" << endl;
  cout << "\u2502 Test FTridend's kernel \u2502" << endl;
  cout << "\u2514";
  for (int i = 0; i < 24; ++i) cout << "\u2500";
  cout << "\u2518" << endl;


  launch(test_BSet, "BSet");
  launch(test_SchroederForest, "SchroederForest");

}

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

#include "../kernel/schroeder_tree.hpp"
#include "../kernel/schroeder_forest.hpp"
#include "../kernel/quasi_shuffle.hpp"
#include "../kernel/tridend_schroeder_algebra.hpp"

using namespace std;

int main() {
  //SchroederTree T = {1, 9, 13, 15, 31, 127};
  //SchroederTree T = {1,9,15,47,431,943,1007,1023};
  //SchroederTree T = {1, 17, 209, 497, 509, 511};
  SchroederTree T = {511, 510, 494, 302, 14, 2};
  T.display();
  bool b = T.validate();
  cout << b <<endl;
  /*auto left = T.left_comb_splitting();
  auto right = T.right_comb_splitting();
  cout << "*************" << endl;
  cout << "* Left comb *" << endl;
  cout << "*************" << endl;
  for (size_t i = 0; i < left.size(); ++i) {
    left[i].display();
  }
  cout << "*************" << endl;
  cout << "* Right comb *" << endl;
  cout << "*************" << endl;
  for (size_t i = 0; i < right.size(); ++i) {
    right[i].display();
    }*/
}

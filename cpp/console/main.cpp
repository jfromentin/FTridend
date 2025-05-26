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
  SchroederTree T1 = {31, 30, 14, 2};
  SchroederTree T2 = {127, 123, 121, 120, 104, 40};
  QuasiShuffle sigma(3, 2);
  do{
    if (sigma[0] == 0 and sigma[1] == 2 and sigma[2] == 3 and sigma[3] == 1 and sigma[4] == 2) {
      sigma.display();
      SchroederTree T(T1, T2, sigma);
      T.display();
      cout <<endl;
    }
  }while(sigma.next());
  
}

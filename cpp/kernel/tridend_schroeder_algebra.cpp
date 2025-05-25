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

#include "tridend_schroeder_algebra.hpp"

SchroederTree TridendSchroederAlgebra::atomic_product(Array<SchroederForest>& left, Array<SchroederForest>& right, QuasiShuffle &sigma) {
  cout << "******************" << endl;
  cout << "* Atomic Product *" << endl;
  cout << "******************" << endl;

  int l = left.size();
  int r = right.size();
  int n = l + r;
  cout << " left = " << l << endl;
  cout << " right = " << r << endl;
  cout << " sigma = ";
  for(int i = 0; i < n; ++i) {
    cout << sigma[i] << ' '; 
  }
  cout << endl;
  
  SchroederTree T;
  return T;
}


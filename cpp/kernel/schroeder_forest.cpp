//****************************************************************************//
//    Copyright (C) 2025 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                                                                            //
//  This file is part of SchroederTree project:                               //
//              <https://github.com/jfromentin/schroeder_tree>                //
//                                                                            //
//  SchroederTree is a free software: you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by the  //
//  Free Software Foundation, either version 3 of the License, or (at your    //
//  option) any later version.                                                //
//                                                                            //
//  SchroederTree is distributed in the hope that it will be useful, but      //
//  WITHOUT ANY WARRANTY; without even the implied warranty of                //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  //
//  Public License for more details.                                          //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with SchroederTree. If not, see <https://www.gnu.org/licenses/>.          //
//****************************************************************************//

#include "schroeder_forest.hpp"

void SchroederForest::display() const {
  cout << "---- Forest ----" << endl;
  SchroederTree::display();
  if (display_forest_size) {
    cout << "> size = " << size << endl;
  }
  cout << "----------------" << endl;
}

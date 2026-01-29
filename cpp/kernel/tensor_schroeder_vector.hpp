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

#ifndef SCHROEDER_TENSOR_HPP
#define SCHROEDER_TENSOR_HPP

#include "schroeder_vector.hpp"

struct ElementarySchroederTensor {
  SchroederTree left;
  SchroederTree right;
};

string to_string(const ElementarySchroederTensor&);

template<> struct std::hash<ElementarySchroederTensor>{
  size_t operator()(const ElementarySchroederTensor& t) const{
    return t.left.hash() ^ (~ t.right.hash());
  }
};

template<class R>
class SchroederTensor{
private:
  unordered_map<ElementarySchroederTreeTensor, R> coeffs;
public:
  SchroederTensor();
  void add(const SchroederTree& tl, const SchroederTree& tr, const R& r = 1);
  void add(const SchroederVector& ul, const SchroederTree& tr);
  
};


string to_string(const ElementarySchroederTensor& t) {
  return to_string(t.left) + "\u2297" + to_string(t.right);
}
#endif

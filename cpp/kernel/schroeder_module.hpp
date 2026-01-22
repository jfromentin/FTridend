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

#ifndef SCHROEDER_MODULE_HPP
#define SCHROEDER_MODULE_HPP

#include "schroeder_vector.hpp"
#include "quasi_shuffle.hpp"


template<class R>
class SchroederModule {
private:
public:
  SchroederModule();
  static SchroederVector<R> product(const SchroederTree& tl, const SchroederTree& tr, PType ptype = PAll);
  static SchroederVector<R> product(const SchroederVector<R>& ul, const SchroederVector<R>& tr, PType ptype = PAll);
};

template<class R>
SchroederModule<R>::SchroederModule() {
}

template<class R>
SchroederVector<R> SchroederModule<R>::product(const SchroederTree& tl, const SchroederTree& tr, PType ptype) {
  //tl.display();
  
  //tr.display();
  int l = tl.right_forests_length();
  int r = tr.left_forests_length();
  QuasiShuffle sigma(l, r, ptype);
  SchroederVector<R> res;
  // int i = 0;
  do {
    //cout << "> " << i << endl;
    //sigma.display();
   
    SchroederTree t(tl, tr, sigma);
    //t.display();
    res.add(t);
    //++ i;
  } while(sigma.next());
  //cout << " Res = " << endl;
  //res.display();
  return res;
}
  

template<class R>
SchroederVector<R> SchroederModule<R>::product(const SchroederVector<R>& ul, const SchroederVector<R>& ur, PType ptype) {
  SchroederVector<R> res;
  for (auto itl = ul.begin(); itl != ul.end(); ++ itl) {
    for (auto itr = ur.begin(); itr != ur.end(); ++ itr) {
      R r = itl -> second * itr -> second;
      res.add(product(itl -> first, itr -> first, ptype), r);
    }
  }
  return res;
}

#endif

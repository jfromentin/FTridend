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


#ifndef ORDERED_PARTITION_HPP
#define ORDERED_PARTITION_HPP

#include "common.hpp"

class OrderedPartition{
private:
  /** Integer \f$n \leq N\f$ associated to the ordered partition. */
  int n;
  
  /** Number of parts l of the ordered partition.*/
  int l;
  
  /** The sequence $(a_0,\ldots,a_{\ell-1})$ defining the ordered partition. */
  int a[N];

public:
  /** Construct the unique ordered partition of 0 */
  OrderedPartition();
  
  /** Construct the ordered partition (n) of n */
  OrderedPartition(int n);

  void initialize();
  
  /** Return the length of the ordered parition. */
  int length() const;
  
  /** Return entry  i of the ordered  partition. */
  int operator[](size_t i) const;


  /** Try to set the current ordered parititon to the next one.
      Return true if we can perform the modification and false otherwise */
  bool next();
  
};

ostream& operator<<(ostream& os, const OrderedPartition& P);

inline
OrderedPartition::OrderedPartition() {
  n = 0;
  l = 0;
}

inline
OrderedPartition::OrderedPartition(int nn) {
  n = nn;
  assert(0 < n and n < (int)N);
  initialize();
}

inline
int OrderedPartition::length() const {
  return l;
}

inline
int OrderedPartition::operator[](size_t i) const{
  assert((int)i < (int)l);
  return a[i];
}

inline void OrderedPartition::initialize() {
  l = 1;
  a[0] = n;
}

#endif

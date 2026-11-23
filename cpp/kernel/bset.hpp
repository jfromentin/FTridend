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

#ifndef KERNEL_BSET_HPP
#define KERNEL_BSET_HPP

#include <iostream>
#include <cstdint>
#include "common.hpp"

using namespace std;

//**************
//* Class BSet *
//**************

//! A class to represent subset of \f$\{1,\ldots,32\}\f$ with a 32-bits encoding.
/** To each such set corresponds a unique integer between \f$0\f$ and \f$2^{32}-1\f$.
    The integer corresponding to the set \f$S\f$ is given by \f$\sum_{i\in S} 2^{i-1}\f$.
 **/ 
class BSet{
private:
  //! The integer assosiated to the set
  BSet_t data;
public:
  //! Construct the empty set
  BSet();
  
  //! Construct a set from a 32 bits integer n using our coding
  BSet(BSet_t n);
  
  //! Construct a set from a list l of integer
  BSet(const initializer_list<int>& l);

  //! Return the size of the set 
  int size() const;

  //! Convert a set to an integer
  explicit operator BSet_t() const;

  //! Hash function of a set (actually the associated integer)
  size_t hash() const;

  //! Add an element to the set
  //! \param v element to add
  void add_element(int v);

  //! Test if two sets are equal
  bool operator==(const BSet& S) const;

  //! Test if two are different
  bool operator!=(const BSet&) const;

  //! Return the minimal element of the set and -1 if it is empty
  int min() const;
  
  //! Return the maximal element of the set and -1 if it is empty
  int max() const;
 
  //! Test if the current set is empty
  bool is_empty() const;
  
  //! Test if the current set is a subset of another one
  //! /param S another set
  bool is_subset(const BSet& S) const;

  //! Return intersection of the current set with another one
  BSet intersection(const BSet& S) const;

  //! Return then current BSet shifted by t. Element of the returned BSet are x + t where x browse the current bitset. Elements < 1 or > 32 are ignored
  BSet shift(int t) const;
  
  //! Return the BSet [1 .. a]
  static BSet range(int a);
  
  //! Return then BSet [a .. b]
  static BSet range(int a, int b);
};  


//***********************
//* Auxiliary functions *
//***********************

//! Return a string from a BSet.
string to_string(const BSet& s);

//********************
//* Inline functions *
//********************

inline BSet::BSet() {
  data = 0;
}

inline BSet::BSet(BSet_t n):data(n) {
}

inline int BSet::size() const {
  return popcount(data);
}

inline BSet::operator BSet_t() const{
  return (BSet_t)data;
}

inline size_t BSet::hash() const {
  return data;
}

inline int BSet::min() const {
  return (data !=  0 ? (1 + __builtin_ctz(data)) : -1);
}

inline int BSet::max() const {
  return (data !=  0 ? (32 - __builtin_clz(data)) : -1);
}

inline bool BSet::is_empty() const {
  return data == 0;
}

inline bool BSet::is_subset(const BSet& S) const {
  return (data | S.data)  == S.data;
}

inline BSet BSet::intersection(const BSet& S) const {
  return BSet(data & S.data);
}

inline BSet BSet::shift(int t) const {
  return (t > 0) ? data << t : data >> -t;

}
inline bool BSet::operator==(const BSet& a) const {
  return data == a.data;
}

inline bool BSet::operator!=(const BSet& a) const {
  return data != a.data;
}

inline BSet BSet::range(int a) {
  assert(a >= 0);
  assert(a <= 32);
  return  (1 << a) - 1;
}


inline BSet BSet::range(int a, int b) {
  assert(a >= 0);
  assert(b >= 0);
  assert(a <= 32);
  assert(b <= 32);
  return ((a > b) ? 0 : (((1 << (b - a + 1)) - 1) << (a - 1)));    
}

#endif

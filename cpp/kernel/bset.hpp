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

#ifndef BSET_HPP
#define BSET_HPP

#include <iostream>
#include <cstdint>

using namespace std;

//**************
//* Class BSet *
//**************

//! A class to represent subset of \f$\{1,\ldots,32\}\f$ with a 32-bits encoding.
/** To each such set corresponds a unique integer between \f$0\f$ and \f$2^{32}-1\f$.
    The integer corresponding to the set \f$S\f$ is given by \f$\sum_{i\in S} 2^{i-1}\f$.
 **/ 
class BSet{
public:
  //! Maximum element value 
  static const int max_value = 32;
private:
  //! The integer assosiated to the set
  uint32_t data;
public:
  //! Construct the empty set
  BSet();
  //! Construct a set from a 32 bits integer n using our coding
  BSet(uint32_t n);
  //! Construct a set from a list l of integer
  BSet(const initializer_list<int>& l);

  //! Return the size of the set 
  int size() const;
  
  
  //! Convert a set to a 32 bit integer
  explicit operator uint64_t() const;
  //! Hash function of a set (actually the associated integer)
  size_t hash() const;

  //! Add an element to the set
  //! \param v element to add
  void add_element(int v);
  
  //! Test if two sets are equal
  bool operator==(const BSet& s) const;
  //! Test if two are different
  bool operator!=(const BSet&) const;
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

inline BSet::BSet(uint32_t n):data(n) {
}

inline BSet::operator uint64_t() const{
  return (uint64_t)data;
}

inline size_t BSet::hash() const {
  return data;
}

inline bool BSet::operator==(const BSet& a) const {
  return data == a.data;
}

inline bool BSet::operator!=(const BSet& a) const {
  return data != a.data;
}

inline int BSet::size() const {
  return popcount(data);
}
#endif

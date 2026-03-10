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

#ifndef KERNEL_SCHROEDER_FOREST_HPP
#define KERNEL_SCHROEDER_FOREST_HPP

#include <bit>
#include <initializer_list>

#include "array.hpp"
#include "bset.hpp"
#include "common.hpp"


//! A class for levelled Schroeder forest
/** A levelled Schroeder forest with \f$n+1\f$ leaves is entierly characterized by an
    strictly increasing chain \f$(c_0,\ldots,c_h)\f$ of the poset \f$(\mathcal{P}([1..n]),\subseteq)\f$
    stisfying \f$c_h=[1..n]\f$. */

class SchroederForest{
public:
  static const int max_angles = 32;
protected:
  //! Initial chain partition giving the structure of the forest
  BSet* c;

  //! Number of angles
  uint8_t n;

  //! Height of the forest as a levelled forest, ie, size of the corresponding initial chain - 1
  uint8_t h;
public:
  //! Construct the empty forest
  SchroederForest();

  //! Construct a Schroeder forest with a giveb height
  //! \param h the height of the forest
  //! \param n number of angles of the forest
  //! \raisewarning The SchroederForest is not correcty defined after the call of this constructor
  SchroederForest(int h, int n);
  
  //! Construct a Schroeder forest from a given initial chain
  SchroederForest(const initializer_list<initializer_list<int>>& l);

  //! Destructor
  ~SchroederForest();

  //! Test if the current Schroeder forest is well defined
  bool is_well_defined() const;

  //! Return the height of the tree as a levelled tree
  int height() const;

  //! Return the number of angles of the tree
  int angles() const;

  //! Return a layer of the Schroeder forest
  //! \param i index of the required layer
  BSet layer(int i) const;

  //! Specify a layer of the forest
  //! \param i index of the layer to consider
  //! \param S value to set
  //! \raisewarning The SchroederForest can be in an uncoherent state after a call of this function
  void set_layer(int i, const BSet& S);
  
  //! Display the Schroeder forest using unicode symbols
  void display(ostream& os = cout) const;

  //! Return LaTeX / Tikz code to draw the Schroeder forest
  string to_latex() const;
  
  //! The hash function
  size_t hash() const;

  //! Equality operator
  bool operator==(const SchroederForest& F) const;
};

//---------------------
// Auxiliary functions 
//---------------------

//! Return a string for the chain reprensenting the Schroeder forest F
string to_string(const SchroederForest& F);

//***************************
//* Inline member functions *
//***************************

// Construct the empty SchroederForest
inline
SchroederForest::SchroederForest() {
  // There is no angles
  n = 0;
  // Height is 0
  h = 0;
  // Initial chain
  c = new BSet[1];
  c[0] = 0;
}

// Delete the current SchroederForest
inline
SchroederForest::~SchroederForest() {
  assert(c != nullptr);
  delete[] c;
}

// Return the height 
inline int
SchroederForest::height() const {
  return h;
}

// Return number of angles
inline int
SchroederForest::angles() const {
  return n;
}

// Return a given layer
inline BSet
SchroederForest::layer(int i) const {
  assert (0 <= i and i <= h);
  return c[i];
}

inline size_t
SchroederForest::hash() const {
  size_t res = 0;
  for (int i = 0; i <= h; ++ i) res += c[i].hash();
  return res;		    			     
}

inline bool
SchroederForest::operator==(const SchroederForest& t) const {
  if (h != t.h) return false;
  for (int i = 0; i <= h; ++ i) {
    if (c[i] != t.c[i]) return false;
  }
  return true;
}
#endif

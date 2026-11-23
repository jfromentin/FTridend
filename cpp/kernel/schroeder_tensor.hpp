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
bool operator==(const ElementarySchroederTensor& t1, const ElementarySchroederTensor& t2);

template<> struct std::hash<ElementarySchroederTensor>{
  size_t operator()(const ElementarySchroederTensor& t) const{
    return t.left.hash() ^ (~ t.right.hash());
  }
};

template<class R>
class SchroederTensor{
private:
  unordered_map<ElementarySchroederTensor, R> coeffs;
public:
  SchroederTensor();
  void add(const SchroederTree& tl, const SchroederTree& tr, const R& r = 1);
  void add(const SchroederVector<R>& ul, const SchroederTree& tr, const R& r = 1);
  void add(const SchroederTree& tl, const SchroederVector<R>& ur, const R& r = 1);
  
  void add(const ElementarySchroederTensor& t, const R& r = 1);
  void add(const SchroederTensor<R>& u, const R& r = 1);
  unordered_map<ElementarySchroederTensor, R>::const_iterator begin() const;
  unordered_map<ElementarySchroederTensor, R>::const_iterator end() const;
  bool is_zero() const;
  
};

template<class R> string to_string(const SchroederTensor<R>& U);

template<class R>
SchroederTensor<R>::SchroederTensor() {
  coeffs.clear();
}

template<class R>
void SchroederTensor<R>::add(const SchroederTree& tl, const SchroederTree& tr, const R& r) {
  if (r == 0) return;
  ElementarySchroederTensor t;
  t.left = tl;
  t.right = tr;
  auto it = coeffs.find(t);
  if (it == coeffs.end())  coeffs[t] = r;
  else {
    if (it -> second + r == 0) coeffs.erase(it);
    else it -> second += r;
  }
}

template<class R>
void SchroederTensor<R>::add(const SchroederVector<R>& u, const SchroederTree& t, const R& r) {
  for (auto it = u.begin(); it != u.end(); ++ it) {
    add(it -> first, t, r * it -> second);
  }
}

template<class R>
void SchroederTensor<R>::add(const SchroederTree& t, const SchroederVector<R>& u,  const R& r) {
  for (auto it = u.begin(); it != u.end(); ++ it) {
    add(t, it -> first, r * it -> second);
  }
}


template<class R>
void SchroederTensor<R>::add(const ElementarySchroederTensor& t, const R& r) {
  if (r == 0) return;
  auto it = coeffs.find(t);
  if (it == coeffs.end())  coeffs[t] = r;
  else {
    if (it -> second + r == 0) coeffs.erase(it);
    else it -> second += r;
  }
}

template<class R>
void SchroederTensor<R>::add(const SchroederTensor<R>& u, const R& r) {
  if (r == 0) return;
  for (auto it = u.coeffs.begin(); it != u.coeffs.end(); ++ it) {
    add(it -> first, r * it -> second);
  }
}

template<class R>
inline  unordered_map<ElementarySchroederTensor, R>::const_iterator
SchroederTensor<R>::begin() const {
  return coeffs.begin();
}

template<class R>
inline  unordered_map<ElementarySchroederTensor, R>::const_iterator
SchroederTensor<R>::end() const {
  return coeffs.end();
}

template<class R>
inline bool
SchroederTensor<R>::is_zero() const {
  return coeffs.empty();
}

inline 
string to_string(const ElementarySchroederTensor& t) {
  return to_string(t.left) + "\u2297" + to_string(t.right);
}

template<class R>
string to_string(const SchroederTensor<R>& u) {
  if(u.is_zero()) return "0";
  bool first = true;
  string str = "";
  for (auto it = u.begin(); it != u.end(); ++ it) {
    R c = it -> second;
    if (first) {
      if (c == -1) str += "- ";
      else if (c != 1) str += to_string(c) + " * ";
    }
    else {
      if (c == -1) str += " - ";
      else if (c == 1) str += " + ";
      else if (c > 0) str += " + " + to_string(c) + " * ";
      else str += " -" + to_string(-c) + " * ";
    }
    str += to_string(it -> first);
    first = false;
  }
  return str;
}

inline
bool operator==(const ElementarySchroederTensor& t1, const ElementarySchroederTensor& t2) {
  return t1.left == t2.left and t1.right == t2.right;
}
#endif

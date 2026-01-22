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

#ifndef SCHROEDER_VECTOR_HPP
#define SCHROEDER_VECTOR_HPP

#include <unordered_map>
#include "schroeder_tree.hpp"
#include "quasi_shuffle.hpp"

using namespace std;

template<> struct std::hash<SchroederTree>{
  size_t operator()(const SchroederTree& t) const{
    return t.hash();
  }
};

//!
//! Vector of Schroeder module over ring R
//!


template<class R>
class SchroederVector{
private:
  unordered_map<SchroederTree, R>  coeffs;
public:
  SchroederVector();
  SchroederVector(const SchroederTree& t);
  void add(const SchroederTree& t, const R& r = 1);
  void add(const SchroederVector& u, const R& r = 1);
  void display() const;
  string to_latex() const;
  unordered_map<SchroederTree, R>::const_iterator begin() const;
  unordered_map<SchroederTree, R>::const_iterator end() const;
  size_t hash() const;
  bool operator==(const SchroederVector<R>& u) const;
};


template<class R> struct std::hash<SchroederVector<R>>{
  size_t operator()(const SchroederVector<R>& u) const{
    return u.hash();
  }
};


template<class R>
inline SchroederVector<R>::SchroederVector() {
  coeffs.clear();
}

template<class R>
inline SchroederVector<R>::SchroederVector(const SchroederTree& t) {
  coeffs[t] = 1;
}

template<class R>
void SchroederVector<R>::display() const {
  if (coeffs.empty()) {
    cout << '0' << endl;
    return;
  }
  for (auto it = coeffs.begin(); it != coeffs.end(); ++ it) {
    //if (it != coeffs.begin()) cout << endl;
    cout << "Coefficient : " << it -> second << endl;
    it -> first.display();
  }
}

template<class R>
string SchroederVector<R>::to_latex() const {
  if (coeffs.empty()) return "0";
  bool first = true;
  string str = "";
  for (auto it = coeffs.begin(); it != coeffs.end(); ++ it) {
    R c = it -> second;
    if (first) {
      if (c == -1) str += "-\\,";
      else if (c != 1) str += to_string(c) + "\\,";
    }
    else {
      if (c == -1) str += "\\,-\\,";
      else if (c == 1) str += "\\,+\\,";
      else if (c > 0) str += "\\, +\\," + to_string(c) + "\\,";
      else str += "\\,-\\," + to_string(-c) + "\\,";
    }
    str += it->first.to_latex();
    first = false;
  }
  return str;
}


template<class R>
void SchroederVector<R>::add(const SchroederTree& t, const R& r) {
  if (r == 0) return;
  auto it = coeffs.find(t);
  if (it == coeffs.end())  coeffs[t] = r;
  else {
    if (it -> second + r == 0) coeffs.erase(it);
    else it -> second += r;
  }
}

template<class R>
void SchroederVector<R>::add(const SchroederVector& u, const R& r) {
  if (r == 0) return;
  for (auto it = u.coeffs.begin(); it != u.coeffs.end(); ++ it) {
    add(it -> first, r * it -> second);
  }
}

template<class R>
inline  unordered_map<SchroederTree, R>::const_iterator
SchroederVector<R>::begin() const {
  return coeffs.begin();
}

template<class R>
inline  unordered_map<SchroederTree, R>::const_iterator
SchroederVector<R>::end() const {
  return coeffs.end();
}

template<class R>
inline size_t
SchroederVector<R>::hash() const {
  size_t res = 0;
  for (auto it = coeffs.begin(); it != coeffs.end(); ++ it) {
    res += (it -> first.hash() * (size_t)it -> second);
  }
  return res; 
}

template<class R>
inline bool
SchroederVector<R>::operator==(const SchroederVector<R>& u) const {
  return coeffs == u.coeffs;
}

#endif

#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <unordered_set>
#include <fstream>
#include "schroeder_module.hpp"

using namespace std;


class Primitives{
public:
  unordered_set<SchroederVector<int>> co_dendriform[N];
  unordered_set<SchroederVector<int>> co_associative[N];
  size_t n;
  unordered_set<SchroederVector<int>>::const_iterator tuple[N];
  SchroederVector<int> theta(const SchroederVector<int>&);
  SchroederVector<int> omega(int l,fstream& file);
  SchroederVector<int> omega_left(int first, int last); //
  SchroederVector<int> omega_right_middle(int first, int last); 
public:
  Primitives();
  void init();
  int rank() const;
  int size_co_associative(int i) const;
  int size_co_dendriform(int i) const;
  void display_co_dendriform(int i) const;
  void display_co_associative(int i) const;
  void next(fstream& file);
};

void to_matrix(const unordered_set<SchroederVector<int>>& F);

inline Primitives::Primitives() {
  n = 0;
  for (int i = 0; i < (int)N; ++ i) {
    co_dendriform[i].clear();
    co_associative[i].clear();
  }
}

inline int
Primitives::rank() const {
  return n;
}

inline int
Primitives::size_co_associative(int i) const {
  assert(0 <= i and i < (int)N);
  return co_associative[i].size();
}

inline int
Primitives::size_co_dendriform(int i) const {
  assert(0 <= i and i < (int)N);
  return co_dendriform[i].size();
}

#endif

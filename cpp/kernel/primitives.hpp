#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <unordered_set>
#include "schroeder_module.hpp"

using namespace std;


class Primitives{
private:
  unordered_set<SchroederVector<int>> sets[N];
  size_t n;
  unordered_set<SchroederVector<int>>::const_iterator tuple[N];
  SchroederVector<int> theta(const SchroederVector<int>&);
  SchroederVector<int> omega(int l);
  SchroederVector<int> omega_left(int i);
  SchroederVector<int> omega_right(int i);
public:
  Primitives();
  void init();
  int rank() const;
  int size(int i) const;
  void display(int i) const;
  void next();
};

inline Primitives::Primitives() {
  n = 0;
  for (int i = 0; i < (int)N; ++ i) sets[i].clear();
}

inline int
Primitives::rank() const {
  return n;
}

inline int
Primitives::size(int i) const {
  assert(0 <= i and i < (int)N);
  return sets[i].size();
}


#endif

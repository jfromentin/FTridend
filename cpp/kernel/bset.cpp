#include "bset.hpp"

//********************
//* Member functions *
//********************

// BSet(const initializer_list<int>&)
BSet::BSet(const initializer_list<int>& l) {
  data = 0;
  for (auto it = l.begin(); it != l.end(); ++ it) {
    int v = *it;
    BSet_t p = (1 << (v - 1));
    // Add v if it not already present in the set
    if ((data & p) == 0) data += p;
  }
}

//***********************
//* Auxiliary functions *
//***********************

// to_string(const BSet&)
string to_string(const BSet& s) {
  string res = "{";
  BSet_t n = (BSet_t)s;
  BSet_t p = 1;
  int i = 1;
  bool first = true;
  while (n != 0) {
    if ((n & p) != 0) {
      if (not first) res += ", ";
      res += std::to_string(i);
      first = false;
      n -= p;
    }
    p *= 2;
    ++ i;
  }
  return res + "}";
}

#ifndef SCHROEDER_FOREST_HPP
#define SCHROEDER_FOREST_HPP

#include "schroeder_tree.hpp"

class SchroederForest:public SchroederTree{
private:
  int size;
public:
  SchroederForest();
  SchroederForest(const SchroederTree& T);
  void display() const;
};

inline SchroederForest::SchroederForest(){
}

inline SchroederForest::SchroederForest(const SchroederTree& T): SchroederTree(T) {
  size = n - popcount(p[h - 2]);
}

#endif

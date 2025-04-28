#ifndef SCHROEDER_FOREST_HPP
#define SCHROEDER_FOREST_HPP

#include <bit>
#include "schroeder_tree.hpp"

using namespace std;

class SchroederForest:public SchroederTree{
private:
  int size;
public:
  void compute_size();
  SchroederForest();
  SchroederForest(const SchroederTree& T);
  void display() const;
};

inline SchroederForest::SchroederForest(){
}

inline SchroederForest::SchroederForest(const SchroederTree& T): SchroederTree(T) {
  compute_size(); 
}

inline void SchroederForest::compute_size() {
  size = n - popcount(p[h - 2]);
}
#endif

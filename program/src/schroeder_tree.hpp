#ifndef SCHROEDER_TREE_HPP
#define SCHROEDER_TREE_HPP

#include <bit>
#include <initializer_list>
#include "common.hpp"
#include "array.hpp"

class SchroederForest;

struct ForestInfo{
  Int h;
  Int n;
  Int a; // angle
};

class SchroederTree{
protected:
  Int n; // Number of leaves
  Int h; // Height of the tree
  Int p[N]; // Chain partition giving the structure of the tree
  int number_left_forests;
  int number_right_forests;
  ForestInfo left_forest_infos[N];
  ForestInfo right_forest_infos[N];
  void compute_left_forest_infos();
  void compute_right_forest_infos();
  void initialize();
public:
  SchroederTree();
  SchroederTree(const initializer_list<Int>& l);
  void display() const;

  Array<SchroederForest> left_comb_splitting() const;
  Array<SchroederForest> right_comb_splitting() const;
};


inline SchroederTree::SchroederTree() {
  n = 0;
  h = 0;
  number_left_forests = 0;
  number_right_forests = 0;
}

inline void SchroederTree::initialize() {
  compute_left_forest_infos();
  compute_right_forest_infos();
}

#endif

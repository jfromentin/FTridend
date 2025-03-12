#ifndef SCHROEDER_TREE_HPP
#define SCHROEDER_TREE_HPP

#include <bit>
#include <initializer_list>
#include "common.hpp"
#include "array.hpp"

class SchroederForest;

class SchroederTree{
protected:
  Int n; // Number of leaves
  Int h; // Height of the tree
  Int p[N]; // Chain partition giving the structure of the tree
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
}


#endif

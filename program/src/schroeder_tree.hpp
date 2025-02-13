#ifndef SCHROEDER_TREE_HPP
#define SCHROEDER_TREE_HPP

#include <bit>
#include <initializer_list>
#include "common.hpp"

class SchroederTree{
private:
  Int n; // Number of leaves
  Int h; // Height of the tree
  Int p[N]; // Chain partition giving the structure of the tree
public:
  SchroederTree();
  SchroederTree(const initializer_list<Int>& l);
  void display() const;
};

inline SchroederTree::SchroederTree() {
  n = 0;
  h = 0;
}


#endif

#include "schroeder_forest.hpp"

void SchroederForest::display() const {
  cout << "==== Forest ====" << endl;
  SchroederTree::display();
  cout << "> size = " << size << endl;
}

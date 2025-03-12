#include "schroeder_forest.hpp"

void SchroederForest::display() const {
  cout << "==== Forest ====" << endl;
  SchroederTree::display();
  cout << "----------------" << endl;
  cout << "> size = " << size << endl;
  cout << "================" << endl;
}

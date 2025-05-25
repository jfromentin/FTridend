#include "schroeder_forest.hpp"

void SchroederForest::display() const {
  cout << "---- Forest ----" << endl;
  SchroederTree::display();
  if (display_forest_size) {
    cout << "> size = " << size << endl;
  }
  cout << "----------------" << endl;
}

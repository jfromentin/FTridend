#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"
#include "quasi_shuffle.hpp"
#include "tridend_schroeder_algebra.hpp"

using namespace std;

int main() {
  //SchroederTree T = {1, 9, 13, 15, 31, 127};
  //SchroederTree T = {1,9,15,47,431,943,1007,1023};
  SchroederTree T = {1, 17, 209, 497, 509, 511};
  T.display();
  auto left = T.left_comb_splitting();
  auto right = T.right_comb_splitting();
  cout << "*************" << endl;
  cout << "* Left comb *" << endl;
  cout << "*************" << endl;
  for (size_t i = 0; i < left.size(); ++i) {
    left[i].display();
  }
  cout << "*************" << endl;
  cout << "* Right comb *" << endl;
  cout << "*************" << endl;
  for (size_t i = 0; i < right.size(); ++i) {
    right[i].display();
  }
}

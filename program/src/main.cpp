#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

using namespace std;

int main() {
  SchroederTree T = {2, 3, 11, 43, 59, 63};
  T.display();
  cout << endl;
  T.left_comb_splitting();
  //T.right_comb_splitting();
  /*SchroederTree T2 = {1, 13, 109, 125, 127};
  T2.display();
  SchroederForest F = T2;
    F.display();*/
}

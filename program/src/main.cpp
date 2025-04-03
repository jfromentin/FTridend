#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

using namespace std;

int main() {
  cout << "-------------------" << endl;
  cout << " Schroeder Tree T1 " << endl;
  cout << "-------------------" << endl;

  SchroederTree T1 = {2, 3, 11, 43, 59, 63};
  T1.display();
  cout << endl;
  T1.left_comb_splitting();
  T1.right_comb_splitting();
   cout << endl;
  cout << "-------------------" << endl;
  cout << " Schroeder Tree T2 " << endl;
  cout << "-------------------" << endl;

  SchroederTree T2 = {1, 13, 109, 125, 127};
  T2.display();
  T2.left_comb_splitting();
  T2.right_comb_splitting();
  //SchroederForest F = T2;
  //F.display();
}

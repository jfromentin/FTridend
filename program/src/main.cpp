#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"
#include "quasi_shuffle.hpp"

using namespace std;

int main() {
  

  QuasiShuffle sigma(8, 8);
  int nb = 0;
  do{
    //cout << nb << " : ";
    //sigma.display();
    ++ nb;
  } while(sigma.next());
  cout << "Numbers = " << nb << endl;
    
  /* SchroederTree T = {2, 3, 11, 43, 59, 63};
  //hroederTree T = {1, 13, 109, 125, 127};
  T .display();
  Array<SchroederForest> left = T.left_comb_splitting();
  cout << "*************" << endl;
  cout << "* Left comb *" << endl;
  cout << "*************" << endl;
  cout << "> numbers : " << left.size() << endl;
  for (size_t i = 0; i < left.size(); ++ i) {
    left[i].display();
  }

  Array<SchroederForest> right = T.right_comb_splitting();
  cout << "**************" << endl;
  cout << "* Right comb *" << endl;
  cout << "**************" << endl;
  cout << "> numbers : " << right.size() << endl;
  for (size_t i = 0; i < right.size(); ++ i) {
    right[i].display();
    }*/
}

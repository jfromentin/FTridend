#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"
#include "quasi_shuffle.hpp"
#include "tridend_schroeder_algebra.hpp"

using namespace std;

int main() {
  SchroederTree Tl = {1, 13, 29, 31};
  SchroederTree Tr = {3};
  Tl.display();
  Tr.display();
  Array<SchroederForest> left = Tl.right_comb_splitting();
  cout << "***********************" << endl;
  cout << "* Right comb of Tleft *" << endl;
  cout << "***********************" << endl;
  cout << "> numbers : " << left.size() << endl;
  for (size_t i = 0; i < left.size(); ++ i) {
    left[i].display();
  }
  Array<SchroederForest> right = Tr.left_comb_splitting();
  cout << "**********************" << endl;
  cout << "* Left comb of Tright*" << endl;
  cout << "**********************" << endl;
  cout << "> numbers : " << right.size() << endl;
  for (size_t i = 0; i < right.size(); ++ i) {
    right[i].display();
  }
  TridendSchroederAlgebra TSA;
  QuasiShuffle sigma(2,1);
  do{
    TSA.atomic_product(left, right, sigma);
    break;
    
    
  }while(sigma.next());
  /*//hroederTree T = {1, 13, 109, 125, 127};
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

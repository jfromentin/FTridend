#include "tridend_schroeder_algebra.hpp"

SchroederTree TridendSchroederAlgebra::atomic_product(Array<SchroederForest>& left, Array<SchroederForest>& right, QuasiShuffle &sigma) {
  cout << "******************" << endl;
  cout << "* Atomic Product *" << endl;
  cout << "******************" << endl;

  int l = left.size();
  int r = right.size();
  int n = l + r;
  cout << " left = " << l << endl;
  cout << " right = " << r << endl;
  cout << " sigma = ";
  for(int i = 0; i < n; ++i) {
    cout << sigma[i] << ' '; 
  }
  cout << endl;
  
  SchroederTree T;
  return T;
}


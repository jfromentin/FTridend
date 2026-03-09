#include <iostream>
#include "bset.hpp"

using namespace std;

int main() {
  cout << "\u250C";
  for (int i = 0; i < 24; ++i) cout << "\u2500";
  cout << "\u2510" << endl;
  cout << "\u2502 Test FTridend's kernel \u2502" << endl;
  cout << "\u2514";
  for (int i = 0; i < 24; ++i) cout << "\u2500";
  cout << "\u2518" << endl;


  launch(test_BSet, "BSet");
}

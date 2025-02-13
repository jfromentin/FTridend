#include "schroeder_tree.hpp"

SchroederTree::SchroederTree(const initializer_list<Int>& l) {
  h = l.size() + 1;
  p[0] = 0;
  size_t k = 1;
  Int prev = 0;
  Int v;
  for (auto it = l.begin(); it != l.end(); ++ it) {
    v = *it;
    // Verification of the chain structure
    assert((v | prev) == v);
    p[k ++] = v;
  }
  n = popcount(v);
  assert(v == ((1L << n) - 1));
  ++ n;
}

void SchroederTree::display() const {
  for (size_t j = 0; j < n; ++ j) {
    cout  << char('a' + j) << ' ';
  }
  cout << "  ";
  for (size_t j = 0; j < n - 1; ++ j) {
    cout  << char('0' + j);
  }
  cout << endl;
  for (size_t i = 1; i < h ; ++ i) {
    bool line = false;
    Int f = 1;
    for (size_t j = 0; j < n - 1; ++ j) {
      if (not (p[i - 1] & f)) cout << '|';
      else cout << ' ';
      if ((p[i] & f)) {
	if (not (p[i - 1] & f)) line = true;
      }
      else line = false;
      if (line) cout << '_';
      else cout << ' ';
      
      f *= 2;
    }
    cout << '|';
    cout << " = ";
    f = 1;
    for (size_t j = 0; j < n - 1; ++ j) {
      if (p[i] & f) cout << '*';
      else cout << '.';
      f *= 2;
    }
    cout << " = " << p[i] << endl;
  }
  for (size_t j = 0; j < n - 1; ++ j) {
    cout << "  ";
  }
  cout << '|' << endl;
}

#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

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
      if (not (p[i - 1] & f)) {
	if (line) cout << "\u2524";
        else if ((p[i] & f) == 0) cout << "\u2502";
	else cout << "\u2570";
      }
      else if (line) cout << "\u2500";
      else cout << ' ';
      if ((p[i] & f)) {
	if (not (p[i - 1] & f)) line = true;
      }
      else line = false;
      if (line) cout << "\u2500";
      else cout << ' ';
      
      f *= 2;
    }
    if (line) cout << "\u2524";
    else cout << "\u2502";
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
  cout << "\u2502" << endl;
}

Array<SchroederForest> SchroederTree::left_comb_splitting() const {
  cout << "# Compute left comb splitting" << endl;
  int s = 0; // Size of the comb
  Int pos[N]; // Localisation of each forest of the comb splitting.
  // Forest i will be given as the Schroeder tree of leaves pos[i], ..., pos[i + 1] - 1
  Int hpos[N]; // Time when pos[i] has been computed
  pos[0] = 0;
  hpos[0] = 0;
  int k = 0;
  for (int i = 0; i < h; ++ i) {
    Int f = (1L << pos[s]);
    while (p[i] & f) {
      f *= 2;
      ++ k;
    }
    if (k != pos[s]) {
      ++ s;
      pos[s] = k;
      hpos[s] = i;
    }
  }
  cout << "Comb size : " << s << endl;
  Array<SchroederForest> res(s);
  for (int i = 0; i < s; ++ i) {
    res[i].n = pos[i+1] - pos[i];
    res[i].h = hpos[i+1] - hpos[i];
    res[i].p[0] = 0;
    for (int j = 1; j < res[i].h; ++ j) {
      res[i].p[j] = (p[j + hpos[i]] >> (pos[i] + 1));
    }
    res[i].display();    
  }
  return res;
}


Array<SchroederForest> SchroederTree::right_comb_splitting() const {
  cout << "# Compute right comb splitting" << endl;
  Int f = 1L << (n - 2);
  cout << "First f = " << f << endl;
  int s = 0;
  for (int i = 0; i < h; ++ i) {
    Int g = f;
    while(p[i] & g) g /= 2;
    if (g != f) {
      ++s;
      f = g;
    }
  }
  cout << "Comb size : " << s << endl;
  Array<SchroederForest> res;
  return res;
}

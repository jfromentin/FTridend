#include "schroeder_tree.hpp"
#include "schroeder_forest.hpp"

SchroederTree::SchroederTree(const initializer_list<Int>& l) {
  h = l.size() + 1;
  p[0] = 0;
  size_t k = 1;
  Int prev = 0;
  Int v = 0;
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
  for (int j = 0; j < n; ++ j) {
    cout  << char('a' + j) << ' ';
  }
  if (verbose_display) {
    cout << "  ";
    for (int j = 0; j < n - 1; ++ j) {
      cout  << char('0' + j);
    }
  }
  cout << endl;
  for (int i = 1; i < h ; ++ i) {
    bool line = false;
    Int f = 1;
    for (int j = 0; j < n - 1; ++ j) {
      if (not (p[i - 1] & f)) {
	if (line) {
	  if (p[i] & f) {
	    cout << "\u2534";
	  }
	  else {
	    cout << "\u2524";
	  }
	}
        else if ((p[i] & f) == 0) cout << "\u2502"; //|
	else cout << "\u2570"; //|_
      }
      else if (line) cout << "\u2500"; //-
      else cout << ' ';
      if ((p[i] & f)) {
	if (not (p[i - 1] & f)) line = true;
      }
      else line = false;
      if (line) cout << "\u2500"; //-
      else cout << ' ';
      
      f *= 2;
    }
    if (line) cout << "\u2524"; //-|
    else cout << "\u2502"; //|
    if (verbose_display) {
      cout << " = ";
      f = 1;
      for (int j = 0; j < n - 1; ++ j) {
	if (p[i] & f) cout << '*';
	else cout << '.';
	f *= 2;
      }
      cout << " = " << p[i];
    }
    cout << endl;
  }
  if (display_root) {
    // Display root
    
    for (int j = 0; j < n - 1; ++ j) {
      cout << "  ";
    }
    cout << "\u2567" << endl;
  }
}

Array<SchroederForest> SchroederTree::left_comb_splitting() const {
  int s = 0; // Size of the comb
  Int pos[N]; // Localisation of each forest of the comb splitting.
  // Forest i will be given as the Schroeder tree of leaves pos[i] + 1, ..., pos[i + 1]
  Int hpos[N]; // Time when pos[i] has been computed
  pos[0] = 0;
  hpos[0] = 0;
  int k = 0;
  Int f = 1;
  for (int i = 0; i < h; ++ i) {
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
  Array<SchroederForest> res(s);
  for (int i = 0; i < s; ++ i) {
    res[i].n = pos[i + 1] - pos[i];
    res[i].h = hpos[i + 1] - hpos[i];
 
    res[i].p[0] = 0;
    for (int j = 1; j < res[i].h; ++ j) {
      res[i].p[j] = (p[j + hpos[i]] >> (pos[i] + 1));
    }
    res[i].compute_size();
  }
  return res;
}


Array<SchroederForest> SchroederTree::right_comb_splitting() const {
  int s = 0;
  Int pos[N]; // Localisation of each forest of the comb splitting.
  // Forest i will be given as the Schroeder tree of leaves pos[i + 1] - 1, ..., pos[i]
  
  pos[0] = n - 1;
  Int k = n - 1;
  Int f = 1L << (n - 2);
  for (int i = 0; i < h; ++ i) {
    while(p[i] & f) {
      f /= 2;
      --k;
    }
    if (k != pos[s]) {
      ++s;
      pos[s] = k;
    }
  }
  Int ht = h - 1;
  Int hb;
  Array<SchroederForest> res(s);
    for (int i = 0; i < s; ++ i) {
    int nf = pos[i] - pos[i + 1];
    res[i].n = nf;
    // Right most forest is special leave n does not appeat directly 
    if (i > 0) --nf;
    Int mask = ((1 << nf) - 1) << pos[i + 1];
    while((p[ht] & mask) != 0) --ht;
    hb = ht + 1;
    while((p[hb] & mask) != mask) ++hb;
    int hf = hb - ht + 1;
    res[i].h = hf;
    res[i].p[0] = 0;
    for (int j = 1; j < hf; ++ j) {
      res[i].p[j] = ((p[j + ht] & mask) >> pos[i + 1]);
    }
    res[i].compute_size();  
  }
  return res;
}

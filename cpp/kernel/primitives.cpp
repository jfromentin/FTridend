#include "primitives.hpp"
#include "ordered_partition.hpp"

SchroederVector<int> Primitives::theta(const SchroederVector<int>& u) {
  SchroederTree y = {1};
  SchroederVector<int> v(y);
  return SchroederModule<int>::product(u, v, PMiddle);
}

void Primitives::init() {
  SchroederTree t = {1};
  SchroederVector<int> u(t);
  sets[0].insert(u);
  n = 1;
}

void Primitives::display(int i) const{
  cout << "==== BEGIN ====" << endl;
  int k = 0;
  for (auto it = sets[i].begin(); it != sets[i].end(); ++ it) {
    cout << "> Element " << k << " : " << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END ====" << endl;
}

void Primitives::next() {
  // Apply theta
  unordered_set<SchroederVector<int>>& cur = sets[n];
  unordered_set<SchroederVector<int>>& prev = sets[n - 1];
  for (auto it = prev.begin(); it != prev.end(); ++ it) {
     cur.insert(theta(*it));
  }
  cout << "==== BEGIN CUR ====" << endl;
  int k = 0;
  for (auto it = cur.begin(); it !=  cur.end(); ++ it) {
    cout << "> Element " << k << " : " << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END CUR ====" << endl;
  OrderedPartition p(n + 1);
  p.next();
  do{
    cout << "p = " << p << endl;
    int l = p.length();
     for (int i = 0; i < l; ++ i) tuple[i] = sets[p[i] - 1].begin();
    while (true) {
      // Compute term of the tuple
      SchroederVector<int> u = omega(l);
      
      // Go to next tuple
      int i = 0;
      for (; i < l; ++ i) {
	++ tuple[i];
	if (tuple[i] != sets[p[i] - 1].end()) break;
	tuple[i] = sets[p[i] - 1].begin();
      }
      if (i == l) break;
    }
      
    
  }while(p.next());
  
}

SchroederVector<int> Primitives::omega_left(int l) {
  SchroederVector temp = *tuple[l - 1];
  for (int i = l - 2; i >= 0; -- i) {
    temp = SchroederModule<int>.product(*tuple[i], temp, Pleft);
  }
  return temp;
}

SchroederVector<int> Primitives::omega_left(int l) {
  SchroederVector temp = *tuple[0];
  for (int i = 1; i < l ; ++ i) {
    temp = SchroederModule<int>.product(temp, *tuple[i], Pright);
  }
  return temp;
}

SchroederVector<int> Primitives::omega(int l) {
  SchroederVector<int> u;
  SchroederVector temp;
  int c = 1
  // i = 0
  // To finisj
  
  for (int i = 1; i < l - 1; ++ i) {
    c *= -1;
    SchroederVector<int> ul = omega_left(i);
    SchroederVector<int> ur = omega_right(i + 1);
    temp = SchroederModule<int>.product(ul, tuple[l - 1], Pright);
    temp = SchroederModule<int>.product(temp, ur, Pleft);
    u.add(temp, c);
    // To finish
  }
  // i = l - 1
  // To finish
}

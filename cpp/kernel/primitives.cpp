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
  co_dendriform[0].insert(u);
  co_associative[0].insert(u);
  n = 1;
}

void Primitives::display_co_dendriform(int i) const{
  cout << "==== BEGIN ====" << endl;
  int k = 0;
  for (auto it = co_dendriform[i].begin(); it != co_dendriform[i].end(); ++ it) {
    cout << "> Element " << k << " : " << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END ====" << endl;
}

void Primitives::display_co_associative(int i) const{
  cout << "==== BEGIN ====" << endl;
  int k = 0;
  for (auto it = co_associative[i].begin(); it != co_associative[i].end(); ++ it) {
    cout << "> Element " << k << " : " << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END ====" << endl;
}

void Primitives::next() {
  // Apply theta
  unordered_set<SchroederVector<int>>& theta_src = co_associative[n - 1];
  unordered_set<SchroederVector<int>>& theta_dst = co_dendriform[n];
  for (auto it = theta_src.begin(); it != theta_src.end(); ++ it) {
     theta_dst.insert(theta(*it));
  }
  /*cout << "==== BEGIN CUR ====" << endl;
  int k = 0;
  for (auto it = cur.begin(); it !=  cur.end(); ++ it) {
    cout << "> Element " << k << " : " << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END CUR ====" << endl;*/

  //Apply Omega
  
  unordered_set<SchroederVector<int>>& omega_dst = co_associative[n];

  OrderedPartition p(++ n);

  do{
    /*cout << "-----------" << endl;
    cout << "p = " << p << endl;
    cout << "-----------" << endl;*/
    int l = p.length();
    for (int i = 0; i < l; ++ i) {
      //cout << "Invode degree " << p[i] - 1 << endl;
      tuple[i] = co_dendriform[p[i] - 1].begin();
    }

    while (true) {
      /*cout << "* Tuple : " << endl;
      for (int i = 0; i < l; ++i ){
	cout << "  " << i << " -> ";
	tuple[i] -> display();
	cout << endl;
	}*/

      // Compute term of the tuple
      if (l == 1) {
	cout << "Ici" << endl;
	tuple[0] -> display();
	omega_dst.insert(*tuple[0]);
      }
      else{
	cout << "La" << endl;
	omega_dst.insert(omega(l));
      }
      // Go to next tuple
      int i = 0;
      for (; i < l; ++ i) {
	++ tuple[i];
	if (tuple[i] != co_dendriform[p[i] - 1].end()) break;
	tuple[i] = co_dendriform[p[i] - 1].begin();
      }
      if (i == l) break;
    }
      
    
  }while(p.next());

  
}

SchroederVector<int> Primitives::omega_left(int l) {
  SchroederVector temp = *tuple[l - 1];
  for (int i = l - 2; i >= 0; -- i) {
    temp = SchroederModule<int>::product(*tuple[i], temp, PLeft);
  }
  return temp;
}

SchroederVector<int> Primitives::omega_right_middle(int l) {
  SchroederVector temp = *tuple[0];
  for (int i = 1; i < l ; ++ i) {
    temp = SchroederModule<int>::product(temp, *tuple[i], PRightMiddle);
  }
  return temp;
}

SchroederVector<int> Primitives::omega(int l) {
  // k = l - 1
  SchroederVector<int> u;
  SchroederVector<int> temp, temp_left, temp_right;
  int c = (l % 2 == 0) ? -1 : 1;
  // i = 0
  temp_right = omega_right_middle(1);
  temp = SchroederModule<int>::product(*tuple[l - 1], temp_right, PLeft);
  u.add(temp, c);
  // i in [1, k - 1]
  for (int i = 1; i < l - 1; ++ i) {
    c *= -1;
    SchroederVector<int> temp_left = omega_left(i);
    SchroederVector<int> temp_right = omega_right_middle(i + 1);
    temp = SchroederModule<int>::product(temp_left, *tuple[l - 1], PRightMiddle);
    temp = SchroederModule<int>::product(temp, temp_right, PLeft);
    u.add(temp, c);
    // To finish
  }
  // i = k
  c *= -1;
  temp_left = omega_left(l - 1);
  temp = SchroederModule<int>::product(temp_left, *tuple[l - 1], PRightMiddle);
  u.add(temp, c);
  cout << "u =" << endl;
  u.display();
  return u;
  //  exit(0);

  // i = l - 1
  // To finish
}

#include "primitives.hpp"
#include "ordered_partition.hpp"
#include <flint/fmpq.h>
#include <flint/fmpq_mat.h>


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
    cout << endl << "> Element " << k << " : " << endl << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END ====" << endl;
}

void Primitives::display_co_associative(int i) const{
  cout << "==== BEGIN ====" << endl;
  int k = 0;
  for (auto it = co_associative[i].begin(); it != co_associative[i].end(); ++ it) {
    cout << endl << "> Element " << k << " : " << endl << endl;
    it -> display();
    ++ k;
  }
  cout << "==== END ====" << endl;
}

void Primitives::next(fstream& file) {
  //file << "{\\color{blue}" << endl;
  //file << "\\section{Compute next primitives elements.}" << endl;
  // Apply theta
  unordered_set<SchroederVector<int>>& theta_src = co_associative[n - 1];
  unordered_set<SchroederVector<int>>& theta_dst = co_dendriform[n];
  //file << "\\subsection{Apply $\\Theta$}" << endl;
  //file << "\\begin{align*}" << endl;
  for (auto it = theta_src.begin(); it != theta_src.end(); ++ it) {
    SchroederVector<int> in = *it;
    SchroederVector<int> out = theta(in);
    //file << in.to_latex() << " &\\mapsto " << out.to_latex() << "\\\\" << endl;
    theta_dst.insert(out);
  }
  //file << "\\end{align*} " << endl;
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

  OrderedPartition p(n + 1);
  // Case p = (n + 1)
  // Add co_endriform[n] to co_associative[n]
  for (auto it = theta_dst.begin(); it != theta_dst.end(); ++ it) {
    omega_dst.insert(* it);
  }
  while(p.next()) {
    //file << "\\subsection{Apply $\\Omega$ for partition [" << p << "]}" << endl << endl;
    /*   cout << "-----------" << endl;
    cout << "p = " << p << endl;
    cout << "-----------" << endl;*/
    int l = p.length();
    //file << "Length is " << l << " and so k = $" << l - 1 << "$." << endl << endl;
    for (int i = 0; i < l; ++ i) {
      //cout << "Invode degree " << p[i] - 1 << endl;
      tuple[i] = co_associative[p[i] - 1].begin();
    }
    
    while (true) {
      /*file << endl << "\\subsubsection{Work on} " << endl << "\\[";
      for (int i = 0; i < l; ++i ){
	if (i > 0) file << "\\, \\otimes\\, ";
	file << tuple[i] -> to_latex();

      }
      file << "\\]" << endl;*/

      SchroederVector<int>temp = omega(l, file);
      
      //file << "We obtain \\(" << temp.to_latex() << "\\)." << endl;
      omega_dst.insert(temp);
      

      // Go to next tuple
      int i = 0;
      for (; i < l; ++ i) {
	++ tuple[i];
	if (tuple[i] != co_associative[p[i] - 1].end()) break;
	tuple[i] = co_associative[p[i] - 1].begin();
      }
      if (i == l) break;
    }
       
  }
  ++ n;
  //file << "}" << endl;
}

SchroederVector<int> Primitives::omega_left(int first, int last) {
  SchroederVector temp = *tuple[last];
  for (int i = last - 1; i >= first; -- i) {
    temp = SchroederModule<int>::product(*tuple[i], temp, PLeft);
  }
  return temp;
}

SchroederVector<int> Primitives::omega_right_middle(int first, int last) {
  SchroederVector temp = *tuple[first];
  for (int i = first + 1; i <= last ; ++ i) {
    temp = SchroederModule<int>::product(temp, *tuple[i], PRightMiddle);
  }
  return temp;
}

SchroederVector<int> Primitives::omega(int l, fstream& file) {
  //file << "\\( y = " << tuple[l - 1] -> to_latex()<< "\\)" << endl;
  // k = l - 1
  SchroederVector<int> u;
  SchroederVector<int> temp, temp_left, temp_right;
  int c = (l % 2 == 0) ? -1 : 1;
  // i = 0
  temp_right = omega_right_middle(0, l - 2);
  temp = SchroederModule<int>::product(*tuple[l - 1], temp_right, PLeft);
  //file << "\\[" << endl;
  //file << "y < \\left(" << temp_right.to_latex() << "\\right) = " << temp.to_latex();
  //file << "\\]" << endl;
  
  u.add(temp, c);
  // i in [1, k - 1]
  for (int i = 1; i < l - 1; ++ i) {
    c *= -1;
    SchroederVector<int> temp_left = omega_left(0, i - 1);
    SchroederVector<int> temp_right = omega_right_middle(i, l - 2);
    temp = SchroederModule<int>::product(temp_left, *tuple[l - 1], PRightMiddle);
    temp = SchroederModule<int>::product(temp, temp_right, PLeft);
    //file << "\\[" << endl;
    //file << "\\left(" << temp_left.to_latex() << "\\right) \\geq y < \\left( " << temp_right.to_latex() << "\\right) = " << temp.to_latex();
    //file << "\\]" << endl;
  
    u.add(temp, c);
    // To finish
  }
  // i = k
  c *= -1;
  temp_left = omega_left(0, l - 2);
  temp = SchroederModule<int>::product(temp_left, *tuple[l - 1], PRightMiddle);
  //file << "\\[" << endl;
  //file << "\\left(" << temp_left.to_latex() << " \\right) \\geq y = " << temp.to_latex();
  //file << "\\]" << endl;
  u.add(temp, c);
  
  //cout << "u =" << endl;
  //u.display();

  return u;
  //  exit(0);

  // i = l - 1
  // To finish
}


void to_matrix(const unordered_set<SchroederVector<int>>& F) {
  unordered_map<SchroederTree, int> base;
  int n = 0;
  for (auto it = F.begin(); it != F.end(); ++ it) {
    const SchroederVector<int>& u = *it;
    for (auto itu = u.begin(); itu != u.end(); ++ itu) {
      const SchroederTree& t = itu -> first;
      auto itt = base.find(t);
      if (itt == base.end()) {
	base[t] = n;
	++n;
      }
    }
  }
  fmpq_mat_t A;
  fmpq_mat_init(A, F.size(), n);
  fmpq_mat_zero(A);
  cout << "Image dimension is " << n << endl;
  cout << "Family cardinality is " << F.size() << endl;
  int k = 0;
  int* res = new int[n];
  for(auto it = F.begin(); it != F.end(); ++ it) {
    //cout << "Vector " << k << endl;
    const SchroederVector<int>& u = *it;
    for (int i = 0; i < n; ++ i) {
      res[i] = 0;
    }
    for (auto itu = u.begin(); itu != u.end(); ++ itu) {
      int p = base[itu -> first];
      res[p] = itu -> second;
      fmpq* c = fmpq_mat_entry(A, k, p);
      fmpq_set_si(c, itu -> second, 1);
    }
    //for (int i = 0; i < n; ++ i) cout << res[i] << " ";
    //cout << endl;
    ++ k;
  }
  //fmpq_mat_print(A);
  int rank =  fmpq_mat_rref_fraction_free(A, A);
  cout << "Rank = " << rank << endl;
  //fmpq_mat_print(A);
  fmpq_mat_clear(A);
 
}

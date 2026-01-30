//****************************************************************************//
//    Copyright (C) 2026 Jean Fromentin <jean.fromentin@univ-littoral.fr>     //
//                       Pierre Catoire <catoire_research@proton.me>          //
//                                                                            //
//  This file is part of FTridend <https://github.com/jfromentin/FTridend>    //
//                                                                            //
//  FTridend is free software: you can redistribute it and/or modify it       //
//  under ethe terms of the GNU General Public License as published by the    //
//  Free Software Foundation, either version 3 of the License, or             //
//  (at your option) any later version.                                       //
//                                                                            //
//  FTridend is distributed in the hope that it will be useful, but WITHOUT   //
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or     //
//  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License      //
//  for more details.                                                         //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with FTridend. If not, see <https://www.gnu.org/licenses/>.               //
//****************************************************************************//

#include "../kernel/schroeder_tree.hpp"
#include "../kernel/schroeder_forest.hpp"
#include "../kernel/quasi_shuffle.hpp"
#include "../kernel/schroeder_vector.hpp"
#include "../kernel/schroeder_module.hpp"
#include "../kernel/primitives.hpp"

#include "../kernel/ordered_partition.hpp"

#include "../kernel/packed_word.hpp"

#include <fstream>
using namespace std;


void latex_primitives_output(fstream& file, const unordered_set<SchroederVector<int>>& tab) {
  file << "There is " << tab.size() << " elements." << endl;
  file << "\\begin{enumerate}" << endl;
  for (auto it = tab.begin(); it != tab.end(); ++ it) {
    file << "\\item " << it -> to_latex() << endl;
  }
  file << "\\end{enumerate}" << endl;
  
}
int main() {

  /*  SchroederTree T = {127,126,122,120,24,8};//511, 510,  494, 302, 14, 2}; //127, 123, 121, 120, 104, 40};

  T.display();
  SchroederTensor<int> u = SchroederModule<int>::coproduct(T);
  cout << to_string(u) << endl;
  //PackedWord w = T.packed_word();
  //cout << w << endl;
  //T.simple_cuts();
  exit(0);*/

  string filename = "output.tex";
  string filename_details = "details.tex";
  fstream latex_file, latex_details_file;
  latex_file.open(filename.c_str(), fstream::out | fstream::trunc);
  latex_file << "\\documentclass{amsart}" << endl;
  latex_file << "\\usepackage{fullpage}" << endl;
  latex_file << "\\usepackage{tikz}" << endl;
  latex_file << "\\tikzset{x=0.20cm,y=0.20cm}" << endl;
  latex_file << "\\begin{document}" << endl;

  latex_details_file.open(filename_details.c_str(), fstream::out | fstream::trunc);
  latex_details_file << "\\documentclass{amsart}" << endl;
  latex_details_file << "\\usepackage{fullpage}" << endl;
  latex_details_file << "\\usepackage{tikz}" << endl;
  latex_details_file << "\\tikzset{x=0.20cm,y=0.20cm}" << endl;
  latex_details_file << "\\begin{document}" << endl;
  Primitives P;
  P.init();
  int deg = 8;
  for (int i = 0; i < deg; ++ i) {
    cout << endl;
    cout << "**************" << endl;
    cout << "* Degree = " << i + 1 << " *" << endl;
    cout << "**************" << endl;
    //latex_file << "\\section{Degree " << i + 1 << "}" << endl;
    //latex_details_file << "\\section{Degree " << i + 1 << "}" << endl;
    const unordered_set<SchroederVector<int>>* tab = &P.co_dendriform[i];
    //latex_file << "\\subsection{Co dendriform} " << endl;
    //latex_primitives_output(latex_file, *tab);
    //latex_details_file << "\\subsection{Co dendriform} " << endl;
    //latex_primitives_output(latex_details_file, *tab);
    tab = &P.co_associative[i];
    for(auto it = tab -> begin(); it != tab -> end(); ++it){
      //cout << "------------" << endl;
      //cout << to_string(*it) << endl;
      SchroederTensor<int> u = SchroederModule<int>::coproduct(*it);
      SchroederTree empty;
      u.add(*it, empty, -1);
      u.add(empty, *it, -1);
      if (not u.is_zero()) {
	cout << to_string(*it) << endl;
	cout << to_string(u) << endl;
      }
    }
    cout << endl;

						      
    //to_matrix(*tab);
    //latex_file << "\\subsection{Co associative} " << endl;
    //latex_primitives_output(latex_file, *tab);
    //latex_details_file << "\\subsection{Co associative} " << endl;
    //latex_primitives_output(latex_details_file, *tab);

    
    //cout << line << endl;
    //cout << "* CoDendriform" << i + 1 << " *" << endl;
    //cout << line << endl << endl;;
    //cout << "- There is " << P.size_co_dendriform(i) << " elements" << endl << endl;
  
    //P.display_co_dendriform(i);
    //cout << endl;
    //cout << line << endl;
    //cout << "* CoAssociative  " << i + 1 << " *" << endl;
    //cout << line << endl << endl;
    //cout << "- There is " << P.size_co_associative(i) << " elements" << endl << endl;
    //P.display_co_associative(i);
    if (i < deg - 1) P.next(latex_details_file);
    //cout << endl;
  }
  //SchroederTree T = {127, 123, 121, 120, 104, 40};
  //latex_file << T.to_latex();
  latex_file << "\\end{document}" << endl;
  latex_details_file << "\\end{document}" << endl;
  latex_file.close();
  latex_details_file.close();
  /* SchroederTree T1 = {1};
  T1.display();
  SchroederVector<int> u = SchroederModule<int>::product(T1, T1, PMiddle);
  u.display();
  exit(0);*/

  /*Primitives P;
  P.init();

  int deg = 4;

  string line = "*******************";
  for (int i = 0; i < deg; ++ i) {
    cout << line << endl;
    cout << "* CoDendriform" << i + 1 << " *" << endl;
    cout << line << endl << endl;;
    cout << "- There is " << P.size_co_dendriform(i) << " elements" << endl << endl;
  
    //P.display_co_dendriform(i);
    cout << endl;
    cout << line << endl;
    cout << "* CoAssociative  " << i + 1 << " *" << endl;
    cout << line << endl << endl;
    cout << "- There is " << P.size_co_associative(i) << " elements" << endl << endl;
    //P.display_co_associative(i);
    if (i < deg - 1) P.next();
    cout << endl;
    }*/
  /*  SchroederTree T1 = {3,1};
  SchroederTree T2 = {3,2};
  T1.display();
  T2.display();
  //SchroederTree T1 = {31, 30, 14, 2};*/
  
  /* SchroederTree T2 = {127, 123, 121, 120, 104, 40};
  T2.display();
  T2.to_latex();*/
  //  SchroederModule<int> M;
  /*SchroederVector<int> u = SchroederModule<int>::product(T1, T2);
  u.display();

  cout << "------" << endl;
  SchroederVector<int> v = SchroederModule<int>::product(u, u);
  v.display();*/
  /*SchroederVector<int> u(T1);
  u.display();
  u.add(T2, -3);
  cout << "-----------------" << endl;
  u.display();
  cout << "-----------------" << endl;
  SchroederVector<int> v;
  v.display();
  cout << "++++++" << endl;
  u.add(T1);
  cout << "-----------------" << endl;
  u.display();
  u.add(T1, -2);
  cout << "-----------------" << endl;
  u.display();
  u.add(T2, 3);
  cout << "-----------------" << endl;
  u.display();*/
  /*SchroederTree T2 = {127, 123, 121, 120, 104, 40};
  T1.display();
  T2.display();
  QuasiShuffle sigma(3, 2);
  do{
    if (sigma[0] == 0 and sigma[1] == 2 and sigma[2] == 3 and sigma[3] == 1 and sigma[4] == 2) {
      sigma.display();
      SchroederTree T(T1, T2, sigma);
      T.display();
      cout <<endl;
    }
    }while(sigma.next());*/

  
}

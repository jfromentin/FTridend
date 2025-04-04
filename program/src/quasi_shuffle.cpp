#include "quasi_shuffle.hpp"

void QuasiShuffle::display() const {
  for(int i = 0; i < l + r; ++ i) cout << tab[i] + 1 << ' ';
  cout << endl;
  /*
  int f = (1L << (n - 1));
  for (int i = 0; i < n; ++ i) {
    if (left & f) {
      if (right & f) {
	cout << " \u2500\u253c\u2500" << endl; // Both
      }
      else {
	cout << " \u2500\u2524" << endl; // Left
      }
    }
    else if (right & f) {
      cout << "  \u251c\u2500" << endl; // Right
    }
    else {
      cout << " ?" << endl; // None
    }
    f >>= 1;
  }
  cout << "\u2550\u2550\u2567\u2550\u2550" << endl; // Root*/
 }

void QuasiShuffle::initialize() {
  if (l == 0 or r == 0) {
    type = QSBase;
    int n = l + r;
    for (int i = 0; i < n; ++ i) tab[i] = i;
    tau = nullptr;
  }
  else {
    type = QSLeft;
    tau = new QuasiShuffle(l - 1, r);
    compute_left_sigma();
  }
}


void QuasiShuffle::compute_sigma() {
  switch(type) {
  case QSBase:
    break;
  case QSLeft:
    compute_left_sigma();
    break;
  case QSMiddle:
    compute_middle_sigma();
    break;
  case QSRight:
    compute_right_sigma();
    break;
  default:
    assert(false);
  }
}

void QuasiShuffle::compute_left_sigma() {
  tab[0] = 0;
  int ntau = l + r - 1; // n of tau 
  for (int i = 0; i < ntau; ++ i) {
    tab[i + 1] = tau->tab[i] + 1;
  }
}

void QuasiShuffle::compute_middle_sigma() {
  tab[0] = 0;
  tab[l] = 0;
  if (l == 1 and r == 1) {
    return;
  }
  int ntau = l + r - 2; // n of tau
  int k = 1;
  for (int i = 0; i < ntau; ++ i) {
    if (k == l) ++k;
    tab[k] = tau->tab[i] + 1;
    ++ k;
  }
  
}

void QuasiShuffle::compute_right_sigma() {
  tab[l] = 0;
  int ntau = l + r - 1; // n of tau
  int k = 0;
  for (int i = 0; i < ntau; ++ i) {
    if (k == l) ++k;
    tab[k] = tau->tab[i] + 1;
    ++ k;
  }
}

bool QuasiShuffle::next() {
  if (type == QSBase) return false;
  if (tau -> next()) {
    compute_sigma();
    return true;
  }
  switch(type) {
  case QSLeft:
    type = QSMiddle;
    delete tau;
    tau = new QuasiShuffle(l - 1, r - 1);
    compute_middle_sigma();
    return true;
    break;
  case QSMiddle:
    type = QSRight;
    delete tau;
    tau = new QuasiShuffle(l, r - 1);
    compute_right_sigma();
    return true;
    break;
  default:
    return false;
  }
}


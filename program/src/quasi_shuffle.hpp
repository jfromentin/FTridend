#ifndef QUASI_SHUFFLE_HPP
#define QUASI_SHUFFLE_HPP

#include "common.hpp"

enum QSType {QSBase, QSLeft, QSMiddle, QSRight};

class QuasiShuffle {
private:
  int l, r;
  QSType type;
  QuasiShuffle* tau;
  int tab[N];
  /*int nmin, nmax;
  int n;
  int left;
  int right;
  bool next_right();*/
  void compute_left_sigma();
  void compute_middle_sigma();
  void compute_right_sigma();
  void compute_sigma();
public:
  QuasiShuffle();
  QuasiShuffle(int l, int r);
  void initialize();
  void display() const;
  bool next();
  int rank() const;
};


inline QuasiShuffle::QuasiShuffle() {
  l = 0;
  r = 0;
  tau = nullptr;
}

inline QuasiShuffle::QuasiShuffle(int ll, int rr) {
  l = ll;
  r = rr;
  initialize();
}



#endif


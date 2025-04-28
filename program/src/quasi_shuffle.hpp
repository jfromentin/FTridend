#ifndef QUASI_SHUFFLE_HPP
#define QUASI_SHUFFLE_HPP

#include "common.hpp"
enum PType {PLeft, PMiddle, PRight, PAll};
enum QSType {QSBase, QSLeft, QSMiddle, QSRight};

class QuasiShuffle {
private:
  PType p;
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
  QuasiShuffle(int l, int r, PType ptype = PAll);
  void initialize();
  void display() const;
  bool next();
  int operator[](int i) const;
  
};


inline QuasiShuffle::QuasiShuffle() {
  p = PAll;
  l = 0;
  r = 0;
  tau = nullptr;
}

inline QuasiShuffle::QuasiShuffle(int ll, int rr, PType pp) {
  p = pp;
  l = ll;
  r = rr;
  initialize();
}

inline int QuasiShuffle::operator[](int i) const {
  assert(i < l + r);
  return tab[i];
}


#endif


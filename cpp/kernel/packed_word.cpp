#include "packed_word.hpp"


void
PackedWord::normalize() {
  int min = read(0);
  int max = min;
  for (size_t i = 1; i < s; ++ i) {
    int val = read(i);
    if (val < min) min = val;
    if (val > max) max = val;
  }
  int nv = 1;
  for (int v = min; v <= max; ++ v) {
    bool find = false;
    for (size_t i = 0; i < s; ++ i) {
      if (read(i) == v) {
	find = true;
	write(i, nv);
      }
    }
    if (find) ++nv;
  }
}


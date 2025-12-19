
#include "ordered_partition.hpp"

ostream& operator<<(ostream& os, const OrderedPartition& P){
  os << '{' << P[0];
  for (int i = 1; i < P.length(); ++ i) {
    os << ',' << P[i];
  }
  return os << '}';
}


bool
OrderedPartition::next() {
  for (int i = l - 1; i > -1; -- i) {
    if (a[i] > 1) {
      -- a[i];
      int m = 0;
      for (int j = 0; j <= i; ++ j) m += a[j];
      int r = n - m;
      l = i + 2;
      a[i + 1] = r;
      for (int j = i + 2; j < (int)N; ++ j) a[j] = 0; 
      return true;
    }
  }
  return false;
}


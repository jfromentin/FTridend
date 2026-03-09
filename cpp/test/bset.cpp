#include "bset.hpp"

int test_BSet() {

  // Empty Permutation
  BSet empty;
  test_equal(to_string(empty), "{}");
  test_equal(empty.size(), 0);
  BSet S1 = 19;
  test_equal(to_string(S1), "{1, 2, 5}");
  test_equal(S1.size(), 3);
  BSet S2 = {4,7,10,14, 3, 14};
  test_equal(to_string(S2), "{3, 4, 7, 10, 14}");
  test_equal(S2.size(), 5);
  
  return 0;
}

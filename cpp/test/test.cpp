
#include "test.hpp"

void launch(int (*t)(), string str) {
  cout << " \u2192 " << str <<  " ... ";
  int line = t();
  if (line == 0) cout << "\033[32mpass\033[0m." << endl;
  else cout << "\033[31mfail\033[0m line \033[35m" << line << "\033[0m." << endl;
}

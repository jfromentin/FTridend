#include <iostream>

using namespace std;

#define test_equal(str1, str2) if (str1 != str2) {return __LINE__;}

void launch(int (*)(), string);


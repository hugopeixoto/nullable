#include "hugopeixoto/nullable.h"
#include <iostream>

int main() {
  Nullable<int> x(1);
  Nullable<int> y;
  Nullable<int> z(2);

  std::cout << !x.null() << std::endl;
  std::cout << y.null() << std::endl;
  std::cout << (x == x) << std::endl;
  std::cout << (y == y) << std::endl;
  std::cout << (y != x) << std::endl;
  std::cout << (x != z) << std::endl;

  std::cout << "x value: " << x.get() << std::endl;

  try {
    std::cout << "y value: " << y.get() << std::endl;
  } catch (null_exception e) {
    std::cout << "caught exception: " << e.what() << std::endl;
  }

  return 0;
}

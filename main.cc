#include "hugopeixoto/optional.h"
#include <iostream>

int main() {
  Optional<int> x(1);
  Optional<int> y;
  Optional<int> z(2);

  std::cout << !x.null() << std::endl;
  std::cout << y.null() << std::endl;
  std::cout << (x == x) << std::endl;
  std::cout << (y == y) << std::endl;
  std::cout << (y != x) << std::endl;
  std::cout << (x != z) << std::endl;

  std::cout << "x value: " << x.unwrap() << std::endl;

  try {
    std::cout << "y value: " << y.unwrap() << std::endl;
  } catch (none_exception e) {
    std::cout << "caught exception: " << e.what() << std::endl;
  }

  return 0;
}

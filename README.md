nullable
========

Auxiliar library to handle null values safely.

Example usage:

```c++
#include "hugopeixoto/nullable.h"
#include <iostream>

int main() {
  Nullable<int> x(1);
  Nullable<int> y;

  std::cout << (x.null() ? "null" : "not null") << std::endl;
  std::cout << x.get() << std::endl;

  std::cout << (y.null() ? "null" : "not null") << std::endl;

  try {
    std::cout << y.get() << std::endl;
  } catch (null_exception e) {
    std::cout << "caught exception: " << e.what() << std::endl;
  }

  return 0;
}
```

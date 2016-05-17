optional
========

Auxiliar library to handle empty values safely.

Example usage:

```c++
#include "hugopeixoto/optional.h"
#include <iostream>
#include <string>

int main() {
  auto repeat = [](auto x) { return x+" "+x+" "+x; };
  auto blacklist = [](auto x) {
    if (x == "spam") {
      return Optional<std::string>();
    } else {
      return Optional<std::string>(x);
    }
  };

  const auto values = {
    Optional<std::string>("echo"),
    Optional<std::string>("spam"),
    Optional<std::string>()
  };

  for (auto v : values)
    std::cout << v.none() << std::endl;

  for (auto v : values)
    std::cout << v.orDefault("empty") << std::endl;

  for (const auto& v : values)
    std::cout << v.map(repeat).orDefault("empty") << std::endl;

  for (const auto& v : values)
    std::cout << v.then(blacklist).orDefault("empty") << std::endl;

  try {
    for (const auto& v : values)
      std::cout << v.unwrap() << std::endl;
  } catch (none_exception e) {
    std::cout << "caught exception: " << e.what() << std::endl;
  }

  return 0;
}
```

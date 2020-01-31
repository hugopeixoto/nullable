#include "hugopeixoto/optional.h"
#include <iostream>
#include <string>

int main() {
  auto repeat = [](auto x) { return x+" "+x+" "+x; };
  auto blacklist = [](auto x) {
    if (x == "spam") {
      return optional<std::string>();
    } else {
      return optional<std::string>(x);
    }
  };

  const auto values = {
    optional<std::string>("echo"),
    optional<std::string>("spam"),
    optional<std::string>()
  };

  std::cout << "map:" << std::endl;
  for (auto v : values)
    std::cout << v.map(&std::string::size).value_or(0) << std::endl;

  for (const auto& v : values)
    std::cout << v.map(repeat).value_or("empty") << std::endl;

  std::cout << "then:" << std::endl;
  for (const auto& v : values)
    std::cout << v.then(blacklist).value_or("empty") << std::endl;

  auto empty = optional<int>();
  auto some  = optional<int>(1);

  std::cout << (empty < empty) << (empty == empty) << std::endl;
  std::cout << (empty < some)  << (empty == some)  << std::endl;
  std::cout << (some < empty)  << (some == empty)  << std::endl;
  std::cout << (some < some)   << (some == some)   << std::endl;

  return 0;
}

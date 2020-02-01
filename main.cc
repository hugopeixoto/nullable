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

  int x = 10;
  auto optref = optional<int&>(x);

  std::cout << *optref.map([](auto a) { return a*a; }) << std::endl;
  std::cout << *(optref.then([](auto a) { return optional<int>(a*a); })) << std::endl;
  std::cout << optref.has_value() << std::endl;
  std::cout << optref.value_or(x) << std::endl;

  return 0;
}

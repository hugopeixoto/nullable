#include "hugopeixoto/optional.h"
#include <iostream>
#include <string>

auto password_from_env() {
  auto pw = std::getenv("PASSWORD");
  if (pw == nullptr) {
    return hugopeixoto::optional<std::string>();
  } else {
    return hugopeixoto::optional<std::string>(pw);
  }
}

auto password_from_file() {
  return hugopeixoto::optional<std::string>();
}

auto login_token(const std::string& password) {
  if (password == "hunter2") {
    return hugopeixoto::optional<std::string>("0x0DEFACED");
  } else {
    return hugopeixoto::optional<std::string>();
  }
}

int main() {
  const auto token = password_from_env()
    .or_else(&password_from_file)
    .then(&login_token);

  const auto header = token.map([](const auto& password) {
    return "Authorization: Bearer " + password;
  }).value_or("Authorization: none");

  std::cout << header << std::endl;

  return 0;
}

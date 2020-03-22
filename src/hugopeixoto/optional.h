#ifndef HUGOPEIXOTO_OPTIONAL_H_
#define HUGOPEIXOTO_OPTIONAL_H_

#include <optional>

namespace hugopeixoto {
template <typename T> struct optional : public std::optional<T> {
  using std::optional<T>::optional;

  bool operator<(const optional<T> &rhs) const {
    return ((const std::optional<T> &)*this) < ((const std::optional<T> &)rhs);
  }

  bool operator!=(const optional<T> &rhs) const {
    return ((const std::optional<T> &)*this) != ((const std::optional<T> &)rhs);
  }

  bool operator==(const optional<T> &rhs) const {
    return ((const std::optional<T> &)*this) == ((const std::optional<T> &)rhs);
  }

  template <typename F, typename U>
  auto map(U (F::*pred)() const noexcept) const {
    return map([&](auto e) { return (e.*pred)(); });
  }

  template <typename F, typename U> auto map(U (F::*pred)() const) const {
    return map([&](auto e) { return (e.*pred)(); });
  }

  template <typename F, typename U> auto map(U (F::*pred)()) const {
    return map([&pred](auto e) { return (e.*pred)(); });
  }

  template <typename F, typename U> auto map(U F::*pred) const {
    return map([&](auto e) { return e.*pred; });
  }

  template <typename F> auto map(F pred) const {
    typedef decltype(pred(std::declval<T>())) Ret;

    if (!this->has_value()) {
      return optional<Ret>();
    } else {
      return optional<Ret>(pred(**this));
    }
  }

  template <typename F> auto then(F pred) const {
    typedef decltype(pred(std::declval<T>())) Ret;

    if (!this->has_value()) {
      return Ret();
    } else {
      return pred(**this);
    }
  }

  template <typename F> auto or_else(const F pred) const {
    if (!this->has_value()) {
      return pred();
    } else {
      return *this;
    }
  }
};
}

#endif

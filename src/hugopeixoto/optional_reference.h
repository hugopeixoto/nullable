#ifndef HUGOPEIXOTO_OPTIONAL_REFERENCE_H_
#define HUGOPEIXOTO_OPTIONAL_REFERENCE_H_

#include <optional>

template <typename T> struct optional<T&> : private std::optional<T*> {
  optional() { }
  optional(T& ref) : std::optional<T*>(&ref) { }

  typedef std::optional<T*> super;
  T& operator*() const { return *super::operator*(); }
  bool has_value() const { return super::has_value(); }
  T& value_or(T& def) const { return *super::value_or(&def); }

  bool operator<(const optional<T&>& rhs) const {
    return
      ((const std::optional<T*>&)*this) <
      ((const std::optional<T*>&)rhs);
  }

  bool operator!=(const optional<T>& rhs) const {
    return
      ((const std::optional<T*>&)*this) !=
      ((const std::optional<T*>&)rhs);
  }

  bool operator==(const optional<T>& rhs) const {
    return
      ((const std::optional<T*>&)*this) ==
      ((const std::optional<T*>&)rhs);
  }

  template<typename F, typename U>
  auto map(U (F::*pred)() const noexcept) const {
    return map([&](auto e){ return (e.*pred)(); });
  }

  template<typename F, typename U>
  auto map(U (F::*pred)() const) const {
    return map([&](auto e){ return (e.*pred)(); });
  }

  template<typename F, typename U>
  auto map(U (F::*pred)()) const {
    return map([&pred](auto e){ return (e.*pred)(); });
  }

  template<typename F, typename U>
  auto map(U F::*pred) const {
    return map([&](auto e){ return e.*pred; });
  }

  template<typename F>
  auto map(F pred) const {
    typedef decltype(pred(std::declval<T>())) Ret;

    if (!this->has_value()) {
      return optional<Ret>();
    } else {
      return optional<Ret>(pred(**this));
    }
  }

  template<typename A>
  struct is_optional : public std::false_type {};

  template<typename A>
  struct is_optional<optional<A>> : public std::true_type {};

  template<typename F>
  auto then(F pred) const {
    typedef decltype(pred(std::declval<T>())) Ret;
    static_assert(
      is_optional<Ret>::value,
      "function must return an optional"
    );

    if (!this->has_value()) {
      return Ret();
    } else {
      return pred(**this);
    }
  }
};

#endif

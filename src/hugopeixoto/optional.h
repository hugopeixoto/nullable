#ifndef HUGOPEIXOTO_OPTIONAL_H_
#define HUGOPEIXOTO_OPTIONAL_H_

#include <exception>

class none_exception : public std::exception {
public:
  virtual const char *what() const noexcept {
    return "trying to access an empty value";
  }
};

template <typename T> struct Optional {
  typedef T type;

  Optional() : is_none(true) { }

  Optional(const T &v) : is_none(false), value(v) { }

  bool none() const { return is_none; }

  const T &unwrap() const {
    none_guard();

    return value;
  }

  T &unwrap() {
    none_guard();

    return value;
  }

  template<typename F>
  auto map(F pred) const {
    if (none()) {
      return Optional<decltype(pred(T()))>();
    } else {
      return Optional<decltype(pred(T()))>(pred(unwrap()));
    }
  }

  template<typename F>
  auto then(F pred) const {
    if (none()) {
      return Optional<typename decltype(pred(T()))::type>();
    } else {
      return pred(unwrap());
    }
  }

  auto orDefault(const T& def) const {
    if (none()) {
      return def;
    } else {
      return unwrap();
    }
  }

  auto orElse(const Optional<T>& def) const {
    if (none()) {
      return decltype(*this)(def);
    } else {
      return *this;
    }
  }

  bool operator==(const Optional<T> &other) const {
    if (other.none()) {
      return none();
    }

    if (none()) {
      return false;
    }

    return unwrap() == other.unwrap();
  }

  bool operator<(const Optional<T> &other) const {
    if (other.none()) {
      return false;
    }

    if (none()) {
      return true;
    }

    return unwrap() < other.unwrap();
  }

  bool operator!=(const Optional<T> &other) const {
    return !(operator==(other));
  }

protected:
  void none_guard() const {
    if (none()) {
      throw none_exception();
    }
  }

  bool is_none;
  T value;
};

template <typename T> bool is_none(const Optional<T> &v) { return v.none(); }

template <typename T> bool is_none(const T &v) { return false; }

#endif

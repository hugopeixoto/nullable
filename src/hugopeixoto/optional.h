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

  Optional() : is_null(true) { }

  Optional(const T &v) : is_null(false), value(v) { }

  bool null() const { return is_null; }

  const T &unwrap() const {
    null_guard();

    return value;
  }

  T &unwrap() {
    null_guard();

    return value;
  }

  template<typename F>
  auto then(F pred) const {
    if (null()) {
      return Optional<typename decltype(pred(T()))::type>();
    } else {
      return pred(unwrap());
    }
  }

  auto orElse(const T& def) const {
    if (null()) {
      return decltype(*this)(def);
    } else {
      return *this;
    }
  }

  bool operator==(const Optional<T> &other) const {
    if (null() || other.null()) {
      return null() && other.null();
    } else {
      return unwrap() == other.unwrap();
    }
  }

  bool operator!=(const Optional<T> &other) const {
    return !(operator==(other));
  }

protected:
  void null_guard() const {
    if (null()) {
      throw none_exception();
    }
  }

  bool is_null;
  T value;
};

template <typename T> bool is_null(const Optional<T> &v) { return v.null(); }

template <typename T> bool is_null(const T &v) { return false; }

#endif

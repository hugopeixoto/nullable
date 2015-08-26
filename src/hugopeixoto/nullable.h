#ifndef HUGOPEIXOTO_NULLABLE_H_
#define HUGOPEIXOTO_NULLABLE_H_

#include <exception>

class null_exception : public std::exception {
public:
  virtual const char *what() const noexcept {
    return "trying to access a null";
  }
};

template <typename T> struct Nullable {
  Nullable() { nullify(); }

  Nullable(const T &v) { set(v); }

  void nullify() { is_null = true; }

  void set(const T &v) {
    value = v;
    is_null = false;
  }

  const T &get() const {
    null_guard();

    return value;
  }

  T &get() {
    null_guard();

    return value;
  }

  operator T &() { return get(); }

  operator const T &() const { return get(); }

  bool operator==(const Nullable<T> &other) const {
    if (null() || other.null()) {
      return null() && other.null();
    } else {
      return get() == other.get();
    }
  }

  bool operator!=(const Nullable<T> &other) const {
    return !(operator==(other));
  }

  void null_guard() const {
    if (null()) {
      throw null_exception();
    }
  }

  bool null() const { return is_null; }

protected:
  bool is_null;
  T value;
};

template <typename T> bool is_null(const Nullable<T> &v) { return v.null(); }

template <typename T> bool is_null(const T &v) { return false; }

#endif

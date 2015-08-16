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

  void null_guard() const {
    if (null()) {
      // print_stack();
      throw null_exception();
    }
  }

  bool null() const { return is_null; }

protected:
  // void print_stack() const {
  //  void *last_frames[20];
  //  size_t last_size;

  //  last_size = backtrace(last_frames, sizeof(last_frames) / sizeof(void *));

  //  backtrace_symbols_fd(last_frames, last_size, 2);
  //}

  bool is_null;
  T value;
};

template <typename T> bool is_null(const Nullable<T> &v) { return v.null(); }

template <typename T> bool is_null(const T &v) { return false; }

#endif

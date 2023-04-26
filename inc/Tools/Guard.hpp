#pragma once

namespace tools {
template <
  class T,
  void (T::*EnterFn)() const,
  void (T::*ExitFn)() const>
class Guard {
public:
  Guard(const T& in_obj) : obj(in_obj) {
    (obj.*EnterFn)();
  }

  Guard(const Guard& other_copy) = delete;

  ~Guard() {
    (obj.*ExitFn)();
  }

private:
  const T& obj;
};
} // namespace tools
#include <cassert>
#include <cstdio>

#include "canon/scalar.hpp"

int main() {
  assert(canon::sqrt(4.0) == 2.0);
  assert(canon::sin(0.0) == 0.0);
  assert(canon::pow(2.0, 10.0) == 1024.0);

  assert(canon::tan(0.0) == 0.0);
  assert(canon::asin(0.0) == 0.0);
  assert(canon::acos(1.0) == 0.0);
  assert(canon::atan(0.0) == 0.0);
  assert(canon::atan2(0.0, 1.0) == 0.0);
  assert(canon::sinh(0.0) == 0.0);
  assert(canon::cosh(0.0) == 1.0);

  std::puts("test_scalar: ok");
  return 0;
}

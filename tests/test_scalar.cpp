#include <cassert>
#include <cstdio>

#include "canon/scalar.hpp"

int main() {
  assert(canon::sqrt(4.0) == 2.0);
  assert(canon::sin(0.0) == 0.0);
  assert(canon::pow(2.0, 10.0) == 1024.0);

  std::puts("test_scalar: ok");
  return 0;
}

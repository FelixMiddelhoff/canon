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

  assert(canon::tanh(0.0) == 0.0);
  assert(canon::asinh(0.0) == 0.0);
  assert(canon::acosh(1.0) == 0.0);
  assert(canon::atanh(0.0) == 0.0);
  assert(canon::cbrt(8.0) == 2.0);
  assert(canon::hypot(3.0, 4.0) == 5.0);
  assert(canon::expm1(0.0) == 0.0);

  assert(canon::log1p(0.0) == 0.0);
  assert(canon::log2(8.0) == 3.0);
  assert(canon::log10(1000.0) == 3.0);
  assert(canon::exp2(3.0) == 8.0);
  assert(canon::exp10(3.0) == 1000.0);
  {
    double s, c;
    canon::sincos(0.0, &s, &c);
    assert(s == 0.0);
    assert(c == 1.0);
  }
  assert(canon::rsqrt(4.0) == 0.5);

  assert(canon::erf(0.0) == 0.0);
  assert(canon::erfc(0.0) == 1.0);
  assert(canon::lgamma(1.0) == 0.0);
  assert(canon::tgamma(1.0) == 1.0);
  assert(canon::sinpi(0.0) == 0.0);
  assert(canon::cospi(0.0) == 1.0);
  assert(canon::tanpi(0.0) == 0.0);

  assert(canon::asinpi(0.0) == 0.0);
  assert(canon::acospi(1.0) == 0.0);
  assert(canon::atanpi(0.0) == 0.0);
  assert(canon::atan2pi(0.0, 1.0) == 0.0);
  assert(canon::exp2m1(0.0) == 0.0);
  assert(canon::exp10m1(0.0) == 0.0);
  assert(canon::log2p1(0.0) == 0.0);
  assert(canon::log10p1(0.0) == 0.0);

  std::puts("test_scalar: ok");
  return 0;
}

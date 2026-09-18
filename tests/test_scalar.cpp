#include <cassert>
#include <cstdio>

#include "isobit/scalar.hpp"

int main() {
  assert(isobit::sqrt(4.0) == 2.0);
  assert(isobit::sin(0.0) == 0.0);
  assert(isobit::pow(2.0, 10.0) == 1024.0);

  assert(isobit::tan(0.0) == 0.0);
  assert(isobit::asin(0.0) == 0.0);
  assert(isobit::acos(1.0) == 0.0);
  assert(isobit::atan(0.0) == 0.0);
  assert(isobit::atan2(0.0, 1.0) == 0.0);
  assert(isobit::sinh(0.0) == 0.0);
  assert(isobit::cosh(0.0) == 1.0);

  assert(isobit::tanh(0.0) == 0.0);
  assert(isobit::asinh(0.0) == 0.0);
  assert(isobit::acosh(1.0) == 0.0);
  assert(isobit::atanh(0.0) == 0.0);
  assert(isobit::cbrt(8.0) == 2.0);
  assert(isobit::hypot(3.0, 4.0) == 5.0);
  assert(isobit::expm1(0.0) == 0.0);

  assert(isobit::log1p(0.0) == 0.0);
  assert(isobit::log2(8.0) == 3.0);
  assert(isobit::log10(1000.0) == 3.0);
  assert(isobit::exp2(3.0) == 8.0);
  assert(isobit::exp10(3.0) == 1000.0);
  {
    double s, c;
    isobit::sincos(0.0, &s, &c);
    assert(s == 0.0);
    assert(c == 1.0);
  }
  assert(isobit::rsqrt(4.0) == 0.5);

  assert(isobit::erf(0.0) == 0.0);
  assert(isobit::erfc(0.0) == 1.0);
  assert(isobit::lgamma(1.0) == 0.0);
  assert(isobit::tgamma(1.0) == 1.0);
  assert(isobit::sinpi(0.0) == 0.0);
  assert(isobit::cospi(0.0) == 1.0);
  assert(isobit::tanpi(0.0) == 0.0);

  assert(isobit::asinpi(0.0) == 0.0);
  assert(isobit::acospi(1.0) == 0.0);
  assert(isobit::atanpi(0.0) == 0.0);
  assert(isobit::atan2pi(0.0, 1.0) == 0.0);
  assert(isobit::exp2m1(0.0) == 0.0);
  assert(isobit::exp10m1(0.0) == 0.0);
  assert(isobit::log2p1(0.0) == 0.0);
  assert(isobit::log10p1(0.0) == 0.0);

  assert(isobit::sinf(0.0f) == 0.0f);
  assert(isobit::cosf(0.0f) == 1.0f);
  assert(isobit::sqrtf(4.0f) == 2.0f);
  assert(isobit::expf(0.0f) == 1.0f);
  assert(isobit::logf(1.0f) == 0.0f);
  assert(isobit::powf(2.0f, 10.0f) == 1024.0f);
  assert(isobit::tanf(0.0f) == 0.0f);

  assert(isobit::asinf(0.0f) == 0.0f);
  assert(isobit::acosf(1.0f) == 0.0f);
  assert(isobit::atanf(0.0f) == 0.0f);
  assert(isobit::atan2f(0.0f, 1.0f) == 0.0f);
  assert(isobit::sinhf(0.0f) == 0.0f);
  assert(isobit::coshf(0.0f) == 1.0f);
  assert(isobit::tanhf(0.0f) == 0.0f);

  assert(isobit::asinhf(0.0f) == 0.0f);
  assert(isobit::acoshf(1.0f) == 0.0f);
  assert(isobit::atanhf(0.0f) == 0.0f);
  assert(isobit::cbrtf(8.0f) == 2.0f);
  assert(isobit::hypotf(3.0f, 4.0f) == 5.0f);
  assert(isobit::expm1f(0.0f) == 0.0f);
  assert(isobit::log1pf(0.0f) == 0.0f);

  assert(isobit::log2f(8.0f) == 3.0f);
  assert(isobit::log10f(1000.0f) == 3.0f);
  assert(isobit::exp2f(3.0f) == 8.0f);
  assert(isobit::exp10f(3.0f) == 1000.0f);
  {
    float s, c;
    isobit::sincosf(0.0f, &s, &c);
    assert(s == 0.0f);
    assert(c == 1.0f);
  }
  assert(isobit::rsqrtf(4.0f) == 0.5f);
  assert(isobit::erff(0.0f) == 0.0f);

  assert(isobit::erfcf(0.0f) == 1.0f);
  assert(isobit::lgammaf(1.0f) == 0.0f);
  assert(isobit::tgammaf(1.0f) == 1.0f);
  assert(isobit::sinpif(0.0f) == 0.0f);
  assert(isobit::cospif(0.0f) == 1.0f);
  assert(isobit::tanpif(0.0f) == 0.0f);
  assert(isobit::asinpif(0.0f) == 0.0f);

  assert(isobit::acospif(1.0f) == 0.0f);
  assert(isobit::atanpif(0.0f) == 0.0f);
  assert(isobit::atan2pif(0.0f, 1.0f) == 0.0f);
  assert(isobit::exp2m1f(0.0f) == 0.0f);
  assert(isobit::exp10m1f(0.0f) == 0.0f);
  assert(isobit::log2p1f(0.0f) == 0.0f);
  assert(isobit::log10p1f(0.0f) == 0.0f);

  std::puts("test_scalar: ok");
  return 0;
}

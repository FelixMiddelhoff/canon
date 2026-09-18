// Prints the raw bit pattern (as hex) of a fixed set of scalar.hpp and
// vecmat.hpp calls. CI runs this on every OS/compiler leg in the matrix and
// diffs the logs — see .github/workflows/ci.yml's bitexact-verify job. A
// mismatch means some function's implementation (or, for dot/multiply, the
// compiler's reduction-order/auto-vectorization behavior under canon's
// required flags) is not actually bit-exact across that pair of legs.
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "canon/scalar.hpp"
#include "canon/vecmat.hpp"

namespace {

void print_bits(const char* label, double v) {
  std::uint64_t bits;
  std::memcpy(&bits, &v, sizeof(bits));
  std::printf("%s: %016llx\n", label, static_cast<unsigned long long>(bits));
}

}  // namespace

int main() {
  print_bits("sin(1.0)", canon::sin(1.0));
  print_bits("cos(1.0)", canon::cos(1.0));
  print_bits("exp(1.0)", canon::exp(1.0));
  print_bits("log(2.0)", canon::log(2.0));
  print_bits("pow(1.0001,1000.0)", canon::pow(1.0001, 1000.0));
  print_bits("sqrt(2.0)", canon::sqrt(2.0));
  print_bits("tan(1.0)", canon::tan(1.0));
  print_bits("asin(0.5)", canon::asin(0.5));
  print_bits("acos(0.5)", canon::acos(0.5));
  print_bits("atan(1.0)", canon::atan(1.0));
  print_bits("atan2(1.0,2.0)", canon::atan2(1.0, 2.0));
  print_bits("sinh(1.0)", canon::sinh(1.0));
  print_bits("cosh(1.0)", canon::cosh(1.0));

  print_bits("tanh(1.0)", canon::tanh(1.0));
  print_bits("asinh(1.0)", canon::asinh(1.0));
  print_bits("acosh(2.0)", canon::acosh(2.0));
  print_bits("atanh(0.5)", canon::atanh(0.5));
  print_bits("cbrt(2.0)", canon::cbrt(2.0));
  print_bits("hypot(3.0,4.0)", canon::hypot(3.0, 4.0));
  print_bits("expm1(1.0)", canon::expm1(1.0));

  print_bits("log1p(1.0)", canon::log1p(1.0));
  print_bits("log2(3.0)", canon::log2(3.0));
  print_bits("log10(3.0)", canon::log10(3.0));
  print_bits("exp2(1.5)", canon::exp2(1.5));
  print_bits("exp10(1.5)", canon::exp10(1.5));
  {
    double s, c;
    canon::sincos(1.0, &s, &c);
    print_bits("sincos(1.0).s", s);
    print_bits("sincos(1.0).c", c);
  }
  print_bits("rsqrt(2.0)", canon::rsqrt(2.0));

  print_bits("erf(1.0)", canon::erf(1.0));
  print_bits("erfc(1.0)", canon::erfc(1.0));
  print_bits("lgamma(2.5)", canon::lgamma(2.5));
  print_bits("tgamma(2.5)", canon::tgamma(2.5));
  print_bits("sinpi(0.25)", canon::sinpi(0.25));
  print_bits("cospi(0.25)", canon::cospi(0.25));
  print_bits("tanpi(0.25)", canon::tanpi(0.25));

  print_bits("asinpi(0.5)", canon::asinpi(0.5));
  print_bits("acospi(0.5)", canon::acospi(0.5));
  print_bits("atanpi(1.0)", canon::atanpi(1.0));
  print_bits("atan2pi(1.0,2.0)", canon::atan2pi(1.0, 2.0));
  print_bits("exp2m1(1.5)", canon::exp2m1(1.5));
  print_bits("exp10m1(1.5)", canon::exp10m1(1.5));
  print_bits("log2p1(1.0)", canon::log2p1(1.0));

  // Reduction-order-sensitive values: mixing large and small magnitudes
  // means a pairwise/tree/SIMD-horizontal sum would round differently
  // than the fixed left-to-right order canon::dot() promises. n=8 is
  // large enough that a compiler willing to auto-vectorize a plain
  // reduction would have room to.
  {
    const double a[8] = {1e16, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0};
    const double b[8] = {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0};
    print_bits("dot(mixed-magnitude,8)", canon::dot(a, b, 8));
  }

  print_bits("normalize(3,4,12).x", canon::normalize(canon::Vec3{3.0, 4.0, 12.0}).x);
  print_bits("normalize(3,4,12).y", canon::normalize(canon::Vec3{3.0, 4.0, 12.0}).y);
  print_bits("normalize(3,4,12).z", canon::normalize(canon::Vec3{3.0, 4.0, 12.0}).z);

  {
    canon::Mat4 m1{{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                     9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}};
    canon::Mat4 m2{{16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0,
                     8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}};
    canon::Mat4 r = canon::multiply(m1, m2);
    for (int i = 0; i < 16; ++i) {
      char label[32];
      std::snprintf(label, sizeof(label), "multiply(m1,m2)[%d]", i);
      print_bits(label, r.m[i]);
    }
  }

  return 0;
}

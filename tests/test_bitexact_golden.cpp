// Prints the raw bit pattern (as hex) of a fixed set of scalar.hpp and
// vecmat.hpp calls. CI runs this on every OS/compiler leg in the matrix and
// diffs the logs — see .github/workflows/ci.yml's bitexact-verify job. A
// mismatch means some function's implementation (or, for dot/multiply, the
// compiler's reduction-order/auto-vectorization behavior under isobit's
// required flags) is not actually bit-exact across that pair of legs.
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "isobit/scalar.hpp"
#include "isobit/vecmat.hpp"

namespace {

void print_bits(const char* label, double v) {
  std::uint64_t bits;
  std::memcpy(&bits, &v, sizeof(bits));
  std::printf("%s: %016llx\n", label, static_cast<unsigned long long>(bits));
}

void print_bits32(const char* label, float v) {
  std::uint32_t bits;
  std::memcpy(&bits, &v, sizeof(bits));
  std::printf("%s: %08x\n", label, bits);
}

}  // namespace

int main() {
  print_bits("sin(1.0)", isobit::sin(1.0));
  print_bits("cos(1.0)", isobit::cos(1.0));
  print_bits("exp(1.0)", isobit::exp(1.0));
  print_bits("log(2.0)", isobit::log(2.0));
  print_bits("pow(1.0001,1000.0)", isobit::pow(1.0001, 1000.0));
  print_bits("sqrt(2.0)", isobit::sqrt(2.0));
  print_bits("tan(1.0)", isobit::tan(1.0));
  print_bits("asin(0.5)", isobit::asin(0.5));
  print_bits("acos(0.5)", isobit::acos(0.5));
  print_bits("atan(1.0)", isobit::atan(1.0));
  print_bits("atan2(1.0,2.0)", isobit::atan2(1.0, 2.0));
  print_bits("sinh(1.0)", isobit::sinh(1.0));
  print_bits("cosh(1.0)", isobit::cosh(1.0));

  print_bits("tanh(1.0)", isobit::tanh(1.0));
  print_bits("asinh(1.0)", isobit::asinh(1.0));
  print_bits("acosh(2.0)", isobit::acosh(2.0));
  print_bits("atanh(0.5)", isobit::atanh(0.5));
  print_bits("cbrt(2.0)", isobit::cbrt(2.0));
  print_bits("hypot(3.0,4.0)", isobit::hypot(3.0, 4.0));
  print_bits("expm1(1.0)", isobit::expm1(1.0));

  print_bits("log1p(1.0)", isobit::log1p(1.0));
  print_bits("log2(3.0)", isobit::log2(3.0));
  print_bits("log10(3.0)", isobit::log10(3.0));
  print_bits("exp2(1.5)", isobit::exp2(1.5));
  print_bits("exp10(1.5)", isobit::exp10(1.5));
  {
    double s, c;
    isobit::sincos(1.0, &s, &c);
    print_bits("sincos(1.0).s", s);
    print_bits("sincos(1.0).c", c);
  }
  print_bits("rsqrt(2.0)", isobit::rsqrt(2.0));

  print_bits("erf(1.0)", isobit::erf(1.0));
  print_bits("erfc(1.0)", isobit::erfc(1.0));
  print_bits("lgamma(2.5)", isobit::lgamma(2.5));
  print_bits("tgamma(2.5)", isobit::tgamma(2.5));
  print_bits("sinpi(0.25)", isobit::sinpi(0.25));
  print_bits("cospi(0.25)", isobit::cospi(0.25));
  print_bits("tanpi(0.25)", isobit::tanpi(0.25));

  print_bits("asinpi(0.5)", isobit::asinpi(0.5));
  print_bits("acospi(0.5)", isobit::acospi(0.5));
  print_bits("atanpi(1.0)", isobit::atanpi(1.0));
  print_bits("atan2pi(1.0,2.0)", isobit::atan2pi(1.0, 2.0));
  print_bits("exp2m1(1.5)", isobit::exp2m1(1.5));
  print_bits("exp10m1(1.5)", isobit::exp10m1(1.5));
  print_bits("log2p1(1.0)", isobit::log2p1(1.0));
  print_bits("log10p1(9.0)", isobit::log10p1(9.0));

  print_bits32("sinf(1.0)", isobit::sinf(1.0f));
  print_bits32("cosf(1.0)", isobit::cosf(1.0f));
  print_bits32("sqrtf(2.0)", isobit::sqrtf(2.0f));
  print_bits32("expf(1.0)", isobit::expf(1.0f));
  print_bits32("logf(2.0)", isobit::logf(2.0f));
  print_bits32("powf(1.0001,20.0)", isobit::powf(1.0001f, 20.0f));
  print_bits32("tanf(1.0)", isobit::tanf(1.0f));

  print_bits32("asinf(0.5)", isobit::asinf(0.5f));
  print_bits32("acosf(0.5)", isobit::acosf(0.5f));
  print_bits32("atanf(1.0)", isobit::atanf(1.0f));
  print_bits32("atan2f(1.0,2.0)", isobit::atan2f(1.0f, 2.0f));
  print_bits32("sinhf(1.0)", isobit::sinhf(1.0f));
  print_bits32("coshf(1.0)", isobit::coshf(1.0f));
  print_bits32("tanhf(1.0)", isobit::tanhf(1.0f));

  print_bits32("asinhf(1.0)", isobit::asinhf(1.0f));
  print_bits32("acoshf(2.0)", isobit::acoshf(2.0f));
  print_bits32("atanhf(0.5)", isobit::atanhf(0.5f));
  print_bits32("cbrtf(2.0)", isobit::cbrtf(2.0f));
  print_bits32("hypotf(3.0,4.0)", isobit::hypotf(3.0f, 4.0f));
  print_bits32("expm1f(1.0)", isobit::expm1f(1.0f));
  print_bits32("log1pf(1.0)", isobit::log1pf(1.0f));

  print_bits32("log2f(3.0)", isobit::log2f(3.0f));
  print_bits32("log10f(3.0)", isobit::log10f(3.0f));
  print_bits32("exp2f(1.5)", isobit::exp2f(1.5f));
  print_bits32("exp10f(1.5)", isobit::exp10f(1.5f));
  {
    float s, c;
    isobit::sincosf(1.0f, &s, &c);
    print_bits32("sincosf(1.0).s", s);
    print_bits32("sincosf(1.0).c", c);
  }
  print_bits32("rsqrtf(2.0)", isobit::rsqrtf(2.0f));
  print_bits32("erff(1.0)", isobit::erff(1.0f));

  print_bits32("erfcf(1.0)", isobit::erfcf(1.0f));
  print_bits32("lgammaf(2.5)", isobit::lgammaf(2.5f));
  print_bits32("tgammaf(2.5)", isobit::tgammaf(2.5f));
  print_bits32("sinpif(0.25)", isobit::sinpif(0.25f));
  print_bits32("cospif(0.25)", isobit::cospif(0.25f));
  print_bits32("tanpif(0.25)", isobit::tanpif(0.25f));
  print_bits32("asinpif(0.5)", isobit::asinpif(0.5f));

  print_bits32("acospif(0.5)", isobit::acospif(0.5f));
  print_bits32("atanpif(1.0)", isobit::atanpif(1.0f));
  print_bits32("atan2pif(1.0,2.0)", isobit::atan2pif(1.0f, 2.0f));
  print_bits32("exp2m1f(1.5)", isobit::exp2m1f(1.5f));
  print_bits32("exp10m1f(1.5)", isobit::exp10m1f(1.5f));
  print_bits32("log2p1f(1.0)", isobit::log2p1f(1.0f));
  print_bits32("log10p1f(9.0)", isobit::log10p1f(9.0f));

  // Reduction-order-sensitive values: mixing large and small magnitudes
  // means a pairwise/tree/SIMD-horizontal sum would round differently
  // than the fixed left-to-right order isobit::dot() promises. n=8 is
  // large enough that a compiler willing to auto-vectorize a plain
  // reduction would have room to.
  {
    const double a[8] = {1e16, 1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0};
    const double b[8] = {1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0};
    print_bits("dot(mixed-magnitude,8)", isobit::dot(a, b, 8));
  }

  print_bits("normalize(3,4,12).x", isobit::normalize(isobit::Vec3{3.0, 4.0, 12.0}).x);
  print_bits("normalize(3,4,12).y", isobit::normalize(isobit::Vec3{3.0, 4.0, 12.0}).y);
  print_bits("normalize(3,4,12).z", isobit::normalize(isobit::Vec3{3.0, 4.0, 12.0}).z);

  {
    isobit::Mat4 m1{{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0,
                     9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0}};
    isobit::Mat4 m2{{16.0, 15.0, 14.0, 13.0, 12.0, 11.0, 10.0, 9.0,
                     8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0}};
    isobit::Mat4 r = isobit::multiply(m1, m2);
    for (int i = 0; i < 16; ++i) {
      char label[32];
      std::snprintf(label, sizeof(label), "multiply(m1,m2)[%d]", i);
      print_bits(label, r.m[i]);
    }
  }

  return 0;
}

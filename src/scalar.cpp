#include "canon/scalar.hpp"

#include <cmath>

// sin/cos/exp/log/pow are all real now: vendored from CORE-MATH (MIT
// license, third_party/core-math/), correctly-rounded and bit-exact across
// x86-64/ARM64 x GCC/Clang/clang-cl given canon's required compile flags.
// (Windows uses clang-cl, not cl.exe — see CMakeLists.txt / ci.yml — since
// the vendored sources need GNU C extensions and, for log/pow, __int128,
// none of which cl.exe supports.)
//
// sqrt is the one function that was never a placeholder: IEEE754 requires
// correctly-rounded sqrt in hardware, so canon::sqrt is bit-exact for free.

extern "C" {
double cr_sin(double x);
double cr_cos(double x);
double cr_exp(double x);
double cr_log(double x);
double cr_pow(double x, double y);
double cr_tan(double x);
double cr_asin(double x);
double cr_acos(double x);
double cr_atan(double x);
double cr_atan2(double y, double x);
double cr_sinh(double x);
double cr_cosh(double x);
double cr_tanh(double x);
double cr_asinh(double x);
double cr_acosh(double x);
double cr_atanh(double x);
double cr_cbrt(double x);
double cr_hypot(double x, double y);
double cr_expm1(double x);
double cr_log1p(double x);
double cr_log2(double x);
double cr_log10(double x);
double cr_exp2(double x);
double cr_exp10(double x);
void cr_sincos(double x, double* s, double* c);
double cr_rsqrt(double x);
double cr_erf(double x);
double cr_erfc(double x);
double cr_lgamma(double x);
double cr_tgamma(double x);
double cr_sinpi(double x);
double cr_cospi(double x);
double cr_tanpi(double x);
double cr_asinpi(double x);
double cr_acospi(double x);
double cr_atanpi(double x);
double cr_atan2pi(double y, double x);
double cr_exp2m1(double x);
double cr_exp10m1(double x);
double cr_log2p1(double x);
double cr_log10p1(double x);
float cr_sinf(float x);
float cr_cosf(float x);
float cr_expf(float x);
float cr_logf(float x);
float cr_powf(float base, float exponent);
float cr_tanf(float x);
float cr_asinf(float x);
float cr_acosf(float x);
float cr_atanf(float x);
float cr_atan2f(float y, float x);
float cr_sinhf(float x);
float cr_coshf(float x);
float cr_tanhf(float x);
}

namespace canon {

double sin(double x) { return cr_sin(x); }
double cos(double x) { return cr_cos(x); }
double sqrt(double x) { return std::sqrt(x); }
double exp(double x) { return cr_exp(x); }
double log(double x) { return cr_log(x); }
double pow(double base, double exponent) { return cr_pow(base, exponent); }

double tan(double x) { return cr_tan(x); }
double asin(double x) { return cr_asin(x); }
double acos(double x) { return cr_acos(x); }
double atan(double x) { return cr_atan(x); }
double atan2(double y, double x) { return cr_atan2(y, x); }
double sinh(double x) { return cr_sinh(x); }
double cosh(double x) { return cr_cosh(x); }

double tanh(double x) { return cr_tanh(x); }
double asinh(double x) { return cr_asinh(x); }
double acosh(double x) { return cr_acosh(x); }
double atanh(double x) { return cr_atanh(x); }
double cbrt(double x) { return cr_cbrt(x); }
double hypot(double x, double y) { return cr_hypot(x, y); }
double expm1(double x) { return cr_expm1(x); }

double log1p(double x) { return cr_log1p(x); }
double log2(double x) { return cr_log2(x); }
double log10(double x) { return cr_log10(x); }
double exp2(double x) { return cr_exp2(x); }
double exp10(double x) { return cr_exp10(x); }
void sincos(double x, double* s, double* c) { cr_sincos(x, s, c); }
double rsqrt(double x) { return cr_rsqrt(x); }

double erf(double x) { return cr_erf(x); }
double erfc(double x) { return cr_erfc(x); }
double lgamma(double x) { return cr_lgamma(x); }
double tgamma(double x) { return cr_tgamma(x); }
double sinpi(double x) { return cr_sinpi(x); }
double cospi(double x) { return cr_cospi(x); }
double tanpi(double x) { return cr_tanpi(x); }

double asinpi(double x) { return cr_asinpi(x); }
double acospi(double x) { return cr_acospi(x); }
double atanpi(double x) { return cr_atanpi(x); }
double atan2pi(double y, double x) { return cr_atan2pi(y, x); }
double exp2m1(double x) { return cr_exp2m1(x); }
double exp10m1(double x) { return cr_exp10m1(x); }
double log2p1(double x) { return cr_log2p1(x); }
double log10p1(double x) { return cr_log10p1(x); }

float sinf(float x) { return cr_sinf(x); }
float cosf(float x) { return cr_cosf(x); }
float sqrtf(float x) { return std::sqrt(x); }
float expf(float x) { return cr_expf(x); }
float logf(float x) { return cr_logf(x); }
float powf(float base, float exponent) { return cr_powf(base, exponent); }
float tanf(float x) { return cr_tanf(x); }

float asinf(float x) { return cr_asinf(x); }
float acosf(float x) { return cr_acosf(x); }
float atanf(float x) { return cr_atanf(x); }
float atan2f(float y, float x) { return cr_atan2f(y, x); }
float sinhf(float x) { return cr_sinhf(x); }
float coshf(float x) { return cr_coshf(x); }
float tanhf(float x) { return cr_tanhf(x); }

}  // namespace canon

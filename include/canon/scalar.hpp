#pragma once

// Correctly-rounded scalar math, guaranteed bit-identical across x86-64,
// ARM64, GCC/Clang/MSVC, at every optimization level, given CANON's
// required compile flags (-ffp-contract=off / -fp:strict — see
// CMakeLists.txt). Every function here trades platform libm's "usually
// close, sometimes off by 1 ULP and never the same 1 ULP twice" for a fixed,
// portable, correctly-rounded implementation.
//
// Full function list and what's intentionally out of scope: docs/scope.md.

namespace canon {

double sin(double x);
double cos(double x);
double sqrt(double x);
double exp(double x);
double log(double x);
double pow(double base, double exponent);

double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double atan2(double y, double x);
double sinh(double x);
double cosh(double x);

double tanh(double x);
double asinh(double x);
double acosh(double x);
double atanh(double x);
double cbrt(double x);
double hypot(double x, double y);
double expm1(double x);

double log1p(double x);
double log2(double x);
double log10(double x);
double exp2(double x);
double exp10(double x);
void sincos(double x, double* s, double* c);
double rsqrt(double x);

double erf(double x);
double erfc(double x);
double lgamma(double x);
double tgamma(double x);
double sinpi(double x);
double cospi(double x);
double tanpi(double x);

double asinpi(double x);
double acospi(double x);
double atanpi(double x);
double atan2pi(double y, double x);
double exp2m1(double x);
double exp10m1(double x);
double log2p1(double x);
double log10p1(double x);

// Single precision (binary32). Named with the libm `f` suffix (sinf, cosf,
// ...) rather than overloaded on the double-precision names above, matching
// both CORE-MATH's own src/binary32/ naming and the C ABI's inability to
// overload (canon_sin vs canon_sinf).
float sinf(float x);
float cosf(float x);
float sqrtf(float x);
float expf(float x);
float logf(float x);
float powf(float base, float exponent);
float tanf(float x);

float asinf(float x);
float acosf(float x);
float atanf(float x);
float atan2f(float y, float x);
float sinhf(float x);
float coshf(float x);
float tanhf(float x);

float asinhf(float x);
float acoshf(float x);
float atanhf(float x);
float cbrtf(float x);
float hypotf(float x, float y);
float expm1f(float x);
float log1pf(float x);

float log2f(float x);
float log10f(float x);
float exp2f(float x);
float exp10f(float x);
void sincosf(float x, float* s, float* c);
float rsqrtf(float x);
float erff(float x);

float erfcf(float x);
float lgammaf(float x);
float tgammaf(float x);
float sinpif(float x);
float cospif(float x);
float tanpif(float x);
float asinpif(float x);

float acospif(float x);
float atanpif(float x);
float atan2pif(float y, float x);
float exp2m1f(float x);
float exp10m1f(float x);
float log2p1f(float x);
float log10p1f(float x);

}  // namespace canon

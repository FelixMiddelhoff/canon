#pragma once

// Correctly-rounded scalar math, guaranteed bit-identical across x86-64,
// ARM64, GCC/Clang/MSVC, at every optimization level, given CANON's
// required compile flags (-ffp-contract=off / -fp:strict — see
// CMakeLists.txt). Every function here trades platform libm's "usually
// close, sometimes off by 1 ULP and never the same 1 ULP twice" for a fixed,
// portable, correctly-rounded implementation.
//
// v0.1 covers the double-precision subset used by simulation/replay/finance
// code most often; f32 and the rest of libm (docs/scope.md) are v1 scope.

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

}  // namespace canon

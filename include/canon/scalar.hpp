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

}  // namespace canon

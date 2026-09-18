#include "canon/scalar.hpp"

#include <cmath>

// sin/cos/exp are real now: vendored from CORE-MATH (MIT license,
// third_party/core-math/), correctly-rounded and bit-exact across
// x86-64/ARM64 x GCC/Clang/MSVC given canon's required compile flags.
//
// log/pow are STILL a <cmath> placeholder — exactly the platform-divergent
// behavior canon exists to replace. Upstream CORE-MATH's log/pow need
// __int128 for their accurate fallback path, which MSVC's cl.exe has no
// equivalent for, and canon's CI matrix builds MSVC without exception.
// Not vendoring until that portability gap has a real answer.
//
// sqrt is the other permanent exception: IEEE754 requires correctly-rounded
// sqrt in hardware, so canon::sqrt is already bit-exact, not a placeholder.

extern "C" {
double cr_sin(double x);
double cr_cos(double x);
double cr_exp(double x);
}

namespace canon {

double sin(double x) { return cr_sin(x); }
double cos(double x) { return cr_cos(x); }
double sqrt(double x) { return std::sqrt(x); }
double exp(double x) { return cr_exp(x); }
double log(double x) { return std::log(x); }
double pow(double base, double exponent) { return std::pow(base, exponent); }

}  // namespace canon

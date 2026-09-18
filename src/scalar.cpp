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
}

namespace canon {

double sin(double x) { return cr_sin(x); }
double cos(double x) { return cr_cos(x); }
double sqrt(double x) { return std::sqrt(x); }
double exp(double x) { return cr_exp(x); }
double log(double x) { return cr_log(x); }
double pow(double base, double exponent) { return cr_pow(base, exponent); }

}  // namespace canon

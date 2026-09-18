#include "canon/scalar.hpp"

#include <cmath>

// PLACEHOLDER IMPLEMENTATION — wraps <cmath>, which is exactly the
// cross-platform-divergent behavior canon exists to replace (see
// canon-planning/canon-START-HERE.md, "what v0.1 actually is"). Kept here
// so the skeleton builds, links and has a passing test on every CI leg from
// day one; the CI matrix's whole job is to prove, in public, the moment this
// wrapper stops being bit-identical across x86-64/ARM64/GCC/Clang/MSVC —
// which is expected, and is the reason the real correctly-rounded
// implementation (docs/scope.md) has to replace it before a 1.0.
//
// sqrt is the one exception: IEEE754 requires correctly-rounded sqrt in
// hardware, so canon::sqrt is already a real, permanent bit-exact
// guarantee, not a placeholder.

namespace canon {

double sin(double x) { return std::sin(x); }
double cos(double x) { return std::cos(x); }
double sqrt(double x) { return std::sqrt(x); }
double exp(double x) { return std::exp(x); }
double log(double x) { return std::log(x); }
double pow(double base, double exponent) { return std::pow(base, exponent); }

}  // namespace canon

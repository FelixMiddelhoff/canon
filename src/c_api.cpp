#include "canon/canon.h"

#include "canon/hash.hpp"
#include "canon/scalar.hpp"
#include "canon/version.hpp"

extern "C" {

double canon_sin(double x) { return canon::sin(x); }
double canon_cos(double x) { return canon::cos(x); }
double canon_sqrt(double x) { return canon::sqrt(x); }
double canon_exp(double x) { return canon::exp(x); }
double canon_log(double x) { return canon::log(x); }
double canon_pow(double base, double exponent) { return canon::pow(base, exponent); }

double canon_tan(double x) { return canon::tan(x); }
double canon_asin(double x) { return canon::asin(x); }
double canon_acos(double x) { return canon::acos(x); }
double canon_atan(double x) { return canon::atan(x); }
double canon_atan2(double y, double x) { return canon::atan2(y, x); }
double canon_sinh(double x) { return canon::sinh(x); }
double canon_cosh(double x) { return canon::cosh(x); }

double canon_tanh(double x) { return canon::tanh(x); }
double canon_asinh(double x) { return canon::asinh(x); }
double canon_acosh(double x) { return canon::acosh(x); }
double canon_atanh(double x) { return canon::atanh(x); }
double canon_cbrt(double x) { return canon::cbrt(x); }
double canon_hypot(double x, double y) { return canon::hypot(x, y); }
double canon_expm1(double x) { return canon::expm1(x); }

double canon_log1p(double x) { return canon::log1p(x); }
double canon_log2(double x) { return canon::log2(x); }
double canon_log10(double x) { return canon::log10(x); }
double canon_exp2(double x) { return canon::exp2(x); }
double canon_exp10(double x) { return canon::exp10(x); }
void canon_sincos(double x, double* s, double* c) { canon::sincos(x, s, c); }
double canon_rsqrt(double x) { return canon::rsqrt(x); }

double canon_erf(double x) { return canon::erf(x); }
double canon_erfc(double x) { return canon::erfc(x); }
double canon_lgamma(double x) { return canon::lgamma(x); }
double canon_tgamma(double x) { return canon::tgamma(x); }
double canon_sinpi(double x) { return canon::sinpi(x); }
double canon_cospi(double x) { return canon::cospi(x); }
double canon_tanpi(double x) { return canon::tanpi(x); }

double canon_asinpi(double x) { return canon::asinpi(x); }
double canon_acospi(double x) { return canon::acospi(x); }
double canon_atanpi(double x) { return canon::atanpi(x); }
double canon_atan2pi(double y, double x) { return canon::atan2pi(y, x); }
double canon_exp2m1(double x) { return canon::exp2m1(x); }
double canon_exp10m1(double x) { return canon::exp10m1(x); }
double canon_log2p1(double x) { return canon::log2p1(x); }
double canon_log10p1(double x) { return canon::log10p1(x); }

uint64_t canon_hash_bits(const double* values, size_t n) { return canon::hash_bits(values, n); }
const char* canon_version_string() { return canon::version_string(); }

}  // extern "C"

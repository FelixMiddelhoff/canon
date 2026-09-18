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

uint64_t canon_hash_bits(const double* values, size_t n) { return canon::hash_bits(values, n); }
const char* canon_version_string() { return canon::version_string(); }

}  // extern "C"

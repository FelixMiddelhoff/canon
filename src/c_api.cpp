#include "isobit/isobit.h"

#include "isobit/hash.hpp"
#include "isobit/scalar.hpp"
#include "isobit/version.hpp"

extern "C" {

double isobit_sin(double x) { return isobit::sin(x); }
double isobit_cos(double x) { return isobit::cos(x); }
double isobit_sqrt(double x) { return isobit::sqrt(x); }
double isobit_exp(double x) { return isobit::exp(x); }
double isobit_log(double x) { return isobit::log(x); }
double isobit_pow(double base, double exponent) { return isobit::pow(base, exponent); }

double isobit_tan(double x) { return isobit::tan(x); }
double isobit_asin(double x) { return isobit::asin(x); }
double isobit_acos(double x) { return isobit::acos(x); }
double isobit_atan(double x) { return isobit::atan(x); }
double isobit_atan2(double y, double x) { return isobit::atan2(y, x); }
double isobit_sinh(double x) { return isobit::sinh(x); }
double isobit_cosh(double x) { return isobit::cosh(x); }

double isobit_tanh(double x) { return isobit::tanh(x); }
double isobit_asinh(double x) { return isobit::asinh(x); }
double isobit_acosh(double x) { return isobit::acosh(x); }
double isobit_atanh(double x) { return isobit::atanh(x); }
double isobit_cbrt(double x) { return isobit::cbrt(x); }
double isobit_hypot(double x, double y) { return isobit::hypot(x, y); }
double isobit_expm1(double x) { return isobit::expm1(x); }

double isobit_log1p(double x) { return isobit::log1p(x); }
double isobit_log2(double x) { return isobit::log2(x); }
double isobit_log10(double x) { return isobit::log10(x); }
double isobit_exp2(double x) { return isobit::exp2(x); }
double isobit_exp10(double x) { return isobit::exp10(x); }
void isobit_sincos(double x, double* s, double* c) { isobit::sincos(x, s, c); }
double isobit_rsqrt(double x) { return isobit::rsqrt(x); }

double isobit_erf(double x) { return isobit::erf(x); }
double isobit_erfc(double x) { return isobit::erfc(x); }
double isobit_lgamma(double x) { return isobit::lgamma(x); }
double isobit_tgamma(double x) { return isobit::tgamma(x); }
double isobit_sinpi(double x) { return isobit::sinpi(x); }
double isobit_cospi(double x) { return isobit::cospi(x); }
double isobit_tanpi(double x) { return isobit::tanpi(x); }

double isobit_asinpi(double x) { return isobit::asinpi(x); }
double isobit_acospi(double x) { return isobit::acospi(x); }
double isobit_atanpi(double x) { return isobit::atanpi(x); }
double isobit_atan2pi(double y, double x) { return isobit::atan2pi(y, x); }
double isobit_exp2m1(double x) { return isobit::exp2m1(x); }
double isobit_exp10m1(double x) { return isobit::exp10m1(x); }
double isobit_log2p1(double x) { return isobit::log2p1(x); }
double isobit_log10p1(double x) { return isobit::log10p1(x); }

float isobit_sinf(float x) { return isobit::sinf(x); }
float isobit_cosf(float x) { return isobit::cosf(x); }
float isobit_sqrtf(float x) { return isobit::sqrtf(x); }
float isobit_expf(float x) { return isobit::expf(x); }
float isobit_logf(float x) { return isobit::logf(x); }
float isobit_powf(float base, float exponent) { return isobit::powf(base, exponent); }
float isobit_tanf(float x) { return isobit::tanf(x); }

float isobit_asinf(float x) { return isobit::asinf(x); }
float isobit_acosf(float x) { return isobit::acosf(x); }
float isobit_atanf(float x) { return isobit::atanf(x); }
float isobit_atan2f(float y, float x) { return isobit::atan2f(y, x); }
float isobit_sinhf(float x) { return isobit::sinhf(x); }
float isobit_coshf(float x) { return isobit::coshf(x); }
float isobit_tanhf(float x) { return isobit::tanhf(x); }

float isobit_asinhf(float x) { return isobit::asinhf(x); }
float isobit_acoshf(float x) { return isobit::acoshf(x); }
float isobit_atanhf(float x) { return isobit::atanhf(x); }
float isobit_cbrtf(float x) { return isobit::cbrtf(x); }
float isobit_hypotf(float x, float y) { return isobit::hypotf(x, y); }
float isobit_expm1f(float x) { return isobit::expm1f(x); }
float isobit_log1pf(float x) { return isobit::log1pf(x); }

float isobit_log2f(float x) { return isobit::log2f(x); }
float isobit_log10f(float x) { return isobit::log10f(x); }
float isobit_exp2f(float x) { return isobit::exp2f(x); }
float isobit_exp10f(float x) { return isobit::exp10f(x); }
void isobit_sincosf(float x, float* s, float* c) { isobit::sincosf(x, s, c); }
float isobit_rsqrtf(float x) { return isobit::rsqrtf(x); }
float isobit_erff(float x) { return isobit::erff(x); }

float isobit_erfcf(float x) { return isobit::erfcf(x); }
float isobit_lgammaf(float x) { return isobit::lgammaf(x); }
float isobit_tgammaf(float x) { return isobit::tgammaf(x); }
float isobit_sinpif(float x) { return isobit::sinpif(x); }
float isobit_cospif(float x) { return isobit::cospif(x); }
float isobit_tanpif(float x) { return isobit::tanpif(x); }
float isobit_asinpif(float x) { return isobit::asinpif(x); }

float isobit_acospif(float x) { return isobit::acospif(x); }
float isobit_atanpif(float x) { return isobit::atanpif(x); }
float isobit_atan2pif(float y, float x) { return isobit::atan2pif(y, x); }
float isobit_exp2m1f(float x) { return isobit::exp2m1f(x); }
float isobit_exp10m1f(float x) { return isobit::exp10m1f(x); }
float isobit_log2p1f(float x) { return isobit::log2p1f(x); }
float isobit_log10p1f(float x) { return isobit::log10p1f(x); }

uint64_t isobit_hash_bits(const double* values, size_t n) { return isobit::hash_bits(values, n); }
const char* isobit_version_string() { return isobit::version_string(); }

}  // extern "C"

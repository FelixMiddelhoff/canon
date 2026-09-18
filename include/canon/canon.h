#ifndef CANON_H
#define CANON_H

/* C ABI surface — for FFI from languages/engines that can't link C++
 * directly. Mirrors the v0.1 scalar + hash surface. */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CANON_SHARED) && defined(_WIN32)
#  ifdef CANON_BUILD_SHARED
#    define CANON_API __declspec(dllexport)
#  else
#    define CANON_API __declspec(dllimport)
#  endif
#else
#  define CANON_API
#endif

CANON_API double canon_sin(double x);
CANON_API double canon_cos(double x);
CANON_API double canon_sqrt(double x);
CANON_API double canon_exp(double x);
CANON_API double canon_log(double x);
CANON_API double canon_pow(double base, double exponent);

CANON_API double canon_tan(double x);
CANON_API double canon_asin(double x);
CANON_API double canon_acos(double x);
CANON_API double canon_atan(double x);
CANON_API double canon_atan2(double y, double x);
CANON_API double canon_sinh(double x);
CANON_API double canon_cosh(double x);

CANON_API double canon_tanh(double x);
CANON_API double canon_asinh(double x);
CANON_API double canon_acosh(double x);
CANON_API double canon_atanh(double x);
CANON_API double canon_cbrt(double x);
CANON_API double canon_hypot(double x, double y);
CANON_API double canon_expm1(double x);

CANON_API double canon_log1p(double x);
CANON_API double canon_log2(double x);
CANON_API double canon_log10(double x);
CANON_API double canon_exp2(double x);
CANON_API double canon_exp10(double x);
CANON_API void canon_sincos(double x, double* s, double* c);
CANON_API double canon_rsqrt(double x);

CANON_API double canon_erf(double x);
CANON_API double canon_erfc(double x);
CANON_API double canon_lgamma(double x);
CANON_API double canon_tgamma(double x);
CANON_API double canon_sinpi(double x);
CANON_API double canon_cospi(double x);
CANON_API double canon_tanpi(double x);

CANON_API double canon_asinpi(double x);
CANON_API double canon_acospi(double x);
CANON_API double canon_atanpi(double x);
CANON_API double canon_atan2pi(double y, double x);
CANON_API double canon_exp2m1(double x);
CANON_API double canon_exp10m1(double x);
CANON_API double canon_log2p1(double x);
CANON_API double canon_log10p1(double x);

CANON_API float canon_sinf(float x);
CANON_API float canon_cosf(float x);
CANON_API float canon_sqrtf(float x);
CANON_API float canon_expf(float x);
CANON_API float canon_logf(float x);
CANON_API float canon_powf(float base, float exponent);
CANON_API float canon_tanf(float x);

CANON_API uint64_t canon_hash_bits(const double* values, size_t n);
CANON_API const char* canon_version_string(void);

#ifdef __cplusplus
}
#endif

#endif /* CANON_H */

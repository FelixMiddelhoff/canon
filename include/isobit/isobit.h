#ifndef ISOBIT_H
#define ISOBIT_H

/* C ABI surface — for FFI from languages/engines that can't link C++
 * directly. Mirrors the scalar + hash surface — see docs/scope.md for
 * the full function list. */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(ISOBIT_SHARED) && defined(_WIN32)
#  ifdef ISOBIT_BUILD_SHARED
#    define ISOBIT_API __declspec(dllexport)
#  else
#    define ISOBIT_API __declspec(dllimport)
#  endif
#else
#  define ISOBIT_API
#endif

ISOBIT_API double isobit_sin(double x);
ISOBIT_API double isobit_cos(double x);
ISOBIT_API double isobit_sqrt(double x);
ISOBIT_API double isobit_exp(double x);
ISOBIT_API double isobit_log(double x);
ISOBIT_API double isobit_pow(double base, double exponent);

ISOBIT_API double isobit_tan(double x);
ISOBIT_API double isobit_asin(double x);
ISOBIT_API double isobit_acos(double x);
ISOBIT_API double isobit_atan(double x);
ISOBIT_API double isobit_atan2(double y, double x);
ISOBIT_API double isobit_sinh(double x);
ISOBIT_API double isobit_cosh(double x);

ISOBIT_API double isobit_tanh(double x);
ISOBIT_API double isobit_asinh(double x);
ISOBIT_API double isobit_acosh(double x);
ISOBIT_API double isobit_atanh(double x);
ISOBIT_API double isobit_cbrt(double x);
ISOBIT_API double isobit_hypot(double x, double y);
ISOBIT_API double isobit_expm1(double x);

ISOBIT_API double isobit_log1p(double x);
ISOBIT_API double isobit_log2(double x);
ISOBIT_API double isobit_log10(double x);
ISOBIT_API double isobit_exp2(double x);
ISOBIT_API double isobit_exp10(double x);
ISOBIT_API void isobit_sincos(double x, double* s, double* c);
ISOBIT_API double isobit_rsqrt(double x);

ISOBIT_API double isobit_erf(double x);
ISOBIT_API double isobit_erfc(double x);
ISOBIT_API double isobit_lgamma(double x);
ISOBIT_API double isobit_tgamma(double x);
ISOBIT_API double isobit_sinpi(double x);
ISOBIT_API double isobit_cospi(double x);
ISOBIT_API double isobit_tanpi(double x);

ISOBIT_API double isobit_asinpi(double x);
ISOBIT_API double isobit_acospi(double x);
ISOBIT_API double isobit_atanpi(double x);
ISOBIT_API double isobit_atan2pi(double y, double x);
ISOBIT_API double isobit_exp2m1(double x);
ISOBIT_API double isobit_exp10m1(double x);
ISOBIT_API double isobit_log2p1(double x);
ISOBIT_API double isobit_log10p1(double x);

ISOBIT_API float isobit_sinf(float x);
ISOBIT_API float isobit_cosf(float x);
ISOBIT_API float isobit_sqrtf(float x);
ISOBIT_API float isobit_expf(float x);
ISOBIT_API float isobit_logf(float x);
ISOBIT_API float isobit_powf(float base, float exponent);
ISOBIT_API float isobit_tanf(float x);

ISOBIT_API float isobit_asinf(float x);
ISOBIT_API float isobit_acosf(float x);
ISOBIT_API float isobit_atanf(float x);
ISOBIT_API float isobit_atan2f(float y, float x);
ISOBIT_API float isobit_sinhf(float x);
ISOBIT_API float isobit_coshf(float x);
ISOBIT_API float isobit_tanhf(float x);

ISOBIT_API float isobit_asinhf(float x);
ISOBIT_API float isobit_acoshf(float x);
ISOBIT_API float isobit_atanhf(float x);
ISOBIT_API float isobit_cbrtf(float x);
ISOBIT_API float isobit_hypotf(float x, float y);
ISOBIT_API float isobit_expm1f(float x);
ISOBIT_API float isobit_log1pf(float x);

ISOBIT_API float isobit_log2f(float x);
ISOBIT_API float isobit_log10f(float x);
ISOBIT_API float isobit_exp2f(float x);
ISOBIT_API float isobit_exp10f(float x);
ISOBIT_API void isobit_sincosf(float x, float* s, float* c);
ISOBIT_API float isobit_rsqrtf(float x);
ISOBIT_API float isobit_erff(float x);

ISOBIT_API float isobit_erfcf(float x);
ISOBIT_API float isobit_lgammaf(float x);
ISOBIT_API float isobit_tgammaf(float x);
ISOBIT_API float isobit_sinpif(float x);
ISOBIT_API float isobit_cospif(float x);
ISOBIT_API float isobit_tanpif(float x);
ISOBIT_API float isobit_asinpif(float x);

ISOBIT_API float isobit_acospif(float x);
ISOBIT_API float isobit_atanpif(float x);
ISOBIT_API float isobit_atan2pif(float y, float x);
ISOBIT_API float isobit_exp2m1f(float x);
ISOBIT_API float isobit_exp10m1f(float x);
ISOBIT_API float isobit_log2p1f(float x);
ISOBIT_API float isobit_log10p1f(float x);

ISOBIT_API uint64_t isobit_hash_bits(const double* values, size_t n);
ISOBIT_API const char* isobit_version_string(void);

#ifdef __cplusplus
}
#endif

#endif /* ISOBIT_H */

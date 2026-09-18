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

CANON_API uint64_t canon_hash_bits(const double* values, size_t n);
CANON_API const char* canon_version_string(void);

#ifdef __cplusplus
}
#endif

#endif /* CANON_H */

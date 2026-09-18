# Function scope

Referenced from `include/isobit/scalar.hpp`. This is the explicit,
authoritative list of what isobit covers — not a vague "rest of libm."

isobit's scope is every function [CORE-MATH](https://core-math.gitlabpages.inria.fr/)
provides a correctly-rounded implementation for, in both `binary64`
(double) and `binary32` (float): source of truth is CORE-MATH's
`src/binary64/` and `src/binary32/` directories. Each is vendored,
verified against a true correctly-rounded reference (`mpmath` at high
precision — `std::`/platform `math` libraries are themselves only
*usually* correctly-rounded, so they're not a trustworthy check), and
covered by the bit-exact golden test.

## Double precision (`binary64`)

`sin`, `cos`, `sqrt`, `exp`, `log`, `pow`, `tan`, `asin`, `acos`, `atan`,
`atan2`, `sinh`, `cosh`, `tanh`, `asinh`, `acosh`, `atanh`, `cbrt`,
`hypot`, `expm1`, `log1p`, `log2`, `log10`, `exp2`, `exp10`, `sincos`,
`rsqrt`, `erf`, `erfc`, `lgamma`, `tgamma`, `sinpi`, `cospi`, `tanpi`,
`asinpi`, `acospi`, `atanpi`, `atan2pi`, `exp2m1`, `exp10m1`, `log2p1`,
`log10p1`.

`sqrt` is bit-exact for free via hardware (IEEE754 mandates
correctly-rounded sqrt); every other function above is vendored from
CORE-MATH (MIT license, `third_party/core-math/`).

## Single precision (`binary32`)

Same functions, `f` suffix, matching CORE-MATH's own naming
(`sinf`, `cosf`, `sqrtf`, `expf`, `logf`, `powf`, `tanf`, `asinf`,
`acosf`, `atanf`, `atan2f`, `sinhf`, `coshf`, `tanhf`, `asinhf`,
`acoshf`, `atanhf`, `cbrtf`, `hypotf`, `expm1f`, `log1pf`, `log2f`,
`log10f`, `exp2f`, `exp10f`, `sincosf`, `rsqrtf`, `erff`, `erfcf`,
`lgammaf`, `tgammaf`, `sinpif`, `cospif`, `tanpif`, `asinpif`,
`acospif`, `atanpif`, `atan2pif`, `exp2m1f`, `exp10m1f`, `log2p1f`,
`log10p1f`) — not C++ overloads of the double-precision names, since the
C ABI (`isobit_sin` vs. `isobit_sinf`) can't overload either.

`sqrtf` is bit-exact for free the same way `sqrt` is; every other f32
function is vendored from CORE-MATH.

Upstream directory names for `binary32` match the `binary64` layout
(e.g. `src/binary32/sin/sinf.c`, not a separate `sinf/` directory) —
only the file inside carries the `f` suffix.

## Vendoring a function

1. Fetch the source from upstream CORE-MATH (MIT license), including any
   per-function local support headers (`dint.h`/`qint.h`/`tint.h`-style
   files live per-function-directory, not shared — check what the file
   actually `#include`s).
2. Vendor into `third_party/core-math/<name>/`, add to
   `ISOBIT_VENDOR_SOURCES` in `CMakeLists.txt`.
3. Wire into `isobit::<name>` in `src/scalar.cpp` (a two-argument function
   like `atan2`/`pow`/`hypot` takes two parameters; `sincos` takes two
   output pointers instead of returning a value).
4. Verify against a true correctly-rounded reference (`mpmath` at high
   precision, not `std::`/platform `math`) on real inputs — linking
   successfully is not verification.
5. Add to `tests/test_bitexact_golden.cpp` so CI's `bitexact-verify` job
   covers it.
6. If a compiler in the CI matrix can't compile the vendored source (as
   MSVC/clang-cl couldn't handle GNU C extensions, `__int128`, or the
   POSIX `signgam` global some functions use), that's a real
   compatibility gap to fix — a compiler-flag or toolchain change, or a
   small force-included compatibility header, never an edit to the
   vendored source itself and never a reason to drop the function.

## Out of scope

- **Anything not `binary64`/`binary32`** — no `long double`, no f16/bf16.
- **Complex-number math.**
- **Elementary/exact operations CORE-MATH doesn't cover**, because they
  are already bit-exact via hardware or trivial bit manipulation, not a
  correctly-rounding problem: `floor`, `ceil`, `round`, `trunc`, `rint`,
  `nearbyint`, `modf`, `frexp`, `ldexp`, `scalbn`, `ilogb`, `fmod`,
  `remainder`, `remquo`, `copysign`, `nextafter`, `nexttoward`, `fmin`,
  `fmax`, `fdim`, `isnan`, `isinf`, `isfinite`, `signbit`. `fma` is also
  out of scope: correctly-rounded fused multiply-add is already an
  IEEE754-mandated hardware primitive where the target has one, the same
  reasoning as `sqrt`, but isobit does not currently wrap it — a caller
  needing a portable bit-exact `fma` should use the compiler/hardware
  intrinsic directly rather than assume isobit covers it.

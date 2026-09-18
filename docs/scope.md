# Function scope: v0.1 vs v1

Referenced from `include/canon/scalar.hpp`. This is the actual list, not
a vague "rest of libm" — v1 is not done until every function below has a
real, vendored, CI-bit-exact-gated implementation, the same bar
sin/cos/sqrt/exp/log/pow already clear.

## v0.1 — done

Double-precision only. All six real (vendored from
[CORE-MATH](https://core-math.gitlabpages.inria.fr/), MIT, except `sqrt`
which is bit-exact for free via hardware), all CI-gated in
`tests/test_bitexact_golden.cpp` / `.github/workflows/ci.yml`'s
`bitexact-verify` job.

- [x] `sin`
- [x] `cos`
- [x] `sqrt`
- [x] `exp`
- [x] `log`
- [x] `pow`

## v1 — required before tagging 1.0

**Full libm, both precisions.** v1 is not "some more functions" — it is
every function below, in both `binary64` (double) and `binary32` (float),
each vendored from CORE-MATH the same way v0.1's six were, each verified
against `std::`/reference values on real inputs before merging, each
added to the bit-exact golden test and gated by CI across the full
os/arch/compiler matrix. No exceptions carved out ahead of time; if a
specific function turns out to need something a target can't provide (the
way `log`/`pow`'s `__int128` need forced the clang-cl decision for
Windows), that gets resolved the same way — fix the real blocker, not
drop the function from scope.

Source of truth for what exists upstream: CORE-MATH's
`src/binary64/` and `src/binary32/` directories.

### Double precision (`binary64`) — target list

- [x] `acos`
- [x] `acosh`
- [x] `acospi`
- [x] `asin`
- [x] `asinh`
- [x] `asinpi`
- [x] `atan`
- [x] `atan2`
- [x] `atan2pi`
- [x] `atanh`
- [x] `atanpi`
- [x] `cbrt`
- [x] `cosh`
- [x] `cospi`
- [x] `erf`
- [x] `erfc`
- [x] `exp10`
- [x] `exp10m1`
- [x] `exp2`
- [x] `exp2m1`
- [x] `expm1`
- [x] `hypot`
- [x] `lgamma`
- [x] `log10`
- [x] `log10p1`
- [x] `log1p`
- [x] `log2`
- [x] `log2p1`
- [x] `rsqrt`
- [x] `sincos`
- [x] `sinh`
- [x] `sinpi`
- [x] `tan`
- [x] `tanh`
- [x] `tanpi`
- [x] `tgamma`

### Single precision (`binary32`) — every v0.1 + above function, `f` suffix

v0.1's six, f32:

- [x] `sinf`
- [x] `cosf`
- [x] `sqrtf` (bit-exact via hardware, no vendoring — same as `sqrt`)
- [x] `expf`
- [x] `logf`
- [x] `powf`

f32 counterpart of every remaining double-precision function above (same
names, `f` suffix, matching CORE-MATH's `src/binary32/` layout — note the
upstream directory names match the f64 ones, e.g. `src/binary32/sin/sinf.c`,
not a separate `sinf/` directory):

- [x] `acosf`
- [x] `acoshf`
- [x] `acospif`
- [x] `asinf`
- [x] `asinhf`
- [x] `asinpif`
- [x] `atanf`
- [x] `atan2f`
- [x] `atan2pif`
- [x] `atanhf`
- [x] `atanpif`
- [x] `cbrtf`
- [x] `coshf`
- [x] `cospif`
- [x] `erff`
- [x] `erfcf`
- [x] `exp10f`
- [x] `exp10m1f`
- [x] `exp2f`
- [x] `exp2m1f`
- [x] `expm1f`
- [x] `hypotf`
- [x] `lgammaf`
- [x] `log10f`
- [x] `log10p1f`
- [x] `log1pf`
- [x] `log2f`
- [x] `log2p1f`
- [x] `rsqrtf`
- [x] `sincosf`
- [x] `sinhf`
- [x] `sinpif`
- [x] `tanf`
- [x] `tanhf`
- [x] `tanpif`
- [x] `tgammaf`

## Process for each new function

Repeats the pattern established for sin/cos/exp/log/pow:

1. Fetch the real source from upstream CORE-MATH (MIT license — already
   verified compatible, see `canon-memory.md` in the planning repo for
   the license check), including any per-function local support headers
   (`dint.h`/`qint.h`-style files live per-function-directory, not
   shared — check what each function actually `#include`s).
2. Vendor into `third_party/core-math/<name>/`, add to
   `CANON_VENDOR_SOURCES` in `CMakeLists.txt`.
3. Wire into `canon::<name>` in `src/scalar.cpp` (or a new header for
   functions with no v0.1 precedent, e.g. `atan2` takes two arguments
   like `pow` does).
4. Verify against `std::`/reference values on real inputs — not just
   "it links" — before treating it as done.
5. Add to `tests/test_bitexact_golden.cpp` so CI's `bitexact-verify`
   job covers it.
6. If cl.exe/clang-cl or any other target in the CI matrix can't compile
   it, that is a blocker to resolve for real (as clang-cl was for
   log/pow's `__int128`), not a reason to skip the function.

## v1 tag gate — all four required, no exceptions

1. All functions above vendored and real.
2. Every function has test coverage (bit-exact golden entry at minimum;
   functions with distinct edge cases — domain errors, poles, special
   values — get their own assertions too).
3. CI passes for real across the full matrix — confirmed via the actual
   run (`gh run view`, job count), not just "the workflow file looks
   right." (A matrix-configuration bug once made CI silently test one leg
   twice instead of all twelve — see `.github/workflows/ci.yml`'s
   comment on `matrix.include` for what to watch for.)
4. **CodeQL ("Security and quality") has zero findings.** Not advisory
   for the 1.0 tag specifically — a hard precondition. Anything flagged
   gets fixed or explicitly dismissed with a documented reason first.

## Out of scope forever (not v1, not planned)

- Anything not double or single precision (no `long double`, no f16/bf16).
- Complex-number math.
- Anything CORE-MATH itself doesn't provide a correctly-rounded
  implementation for.

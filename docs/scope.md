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

- [ ] `acos`
- [ ] `acosh`
- [ ] `acospi`
- [ ] `asin`
- [ ] `asinh`
- [ ] `asinpi`
- [ ] `atan`
- [ ] `atan2`
- [ ] `atan2pi`
- [ ] `atanh`
- [ ] `atanpi`
- [ ] `cbrt`
- [ ] `cosh`
- [ ] `cospi`
- [ ] `erf`
- [ ] `erfc`
- [ ] `exp10`
- [ ] `exp10m1`
- [ ] `exp2`
- [ ] `exp2m1`
- [ ] `expm1`
- [ ] `hypot`
- [ ] `lgamma`
- [ ] `log10`
- [ ] `log10p1`
- [ ] `log1p`
- [ ] `log2`
- [ ] `log2p1`
- [ ] `rsqrt`
- [ ] `sincos`
- [ ] `sinh`
- [ ] `sinpi`
- [ ] `tan`
- [ ] `tanh`
- [ ] `tanpi`
- [ ] `tgamma`

### Single precision (`binary32`) — every v0.1 + above function

- [ ] `sinf`, `cosf`, `sqrtf`, `expf`, `logf`, `powf` (the v0.1 six, f32)
- [ ] `f32` counterpart of every function in the double-precision list
      above (same names, `f` suffix, matching CORE-MATH's
      `src/binary32/` layout)

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

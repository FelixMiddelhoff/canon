# canon

Cross-platform bit-exact math library. Same input, same bits, every
platform.

Status: **pre-alpha skeleton**.

## What this is

glibc, macOS's libm, MSVC's CRT and ARM's libm each implement
sin/cos/exp/log/pow slightly differently — usually within 1 ULP of the
correctly-rounded result, but not the *same* 1 ULP, and not on the same
inputs. That's invisible for most code and fatal for anything that needs
bit-exact reproducibility across machines: deterministic replay, lockstep
simulation, financial/scientific audit trails.

canon replaces the platform-dependent subset of libm with a fixed,
correctly-rounded implementation, plus fixed-reduction-order vector/matrix
ops (SIMD-friendly reductions reorder summation, which also changes the
last bit).

```cpp
double a = canon::sin(x);        // same 64 bits on x86-64, ARM64, any compiler
double d = canon::dot(v1, v2, 3); // fixed left-to-right summation order
```

## Status — read this before relying on the bit-exactness claim

`canon::sin`, `canon::cos`, `canon::exp`, `canon::log`, `canon::pow`,
`canon::sqrt`, `canon::tan`, `canon::asin`, `canon::acos`, `canon::atan`,
`canon::atan2`, `canon::sinh`, `canon::cosh`, `canon::tanh`,
`canon::asinh`, `canon::acosh`, `canon::atanh`, `canon::cbrt`,
`canon::hypot`, `canon::expm1`, `canon::log1p`, `canon::log2`,
`canon::log10`, `canon::exp2`, `canon::exp10`, `canon::sincos`,
`canon::rsqrt`, `canon::erf`, `canon::erfc`, `canon::lgamma`,
`canon::tgamma`, `canon::sinpi`, `canon::cospi`, `canon::tanpi`,
`canon::asinpi`, `canon::acospi`, `canon::atanpi`, `canon::atan2pi`,
`canon::exp2m1`, `canon::exp10m1`, `canon::log2p1`, `canon::log10p1`, and
(single precision) `canon::sinf`, `canon::cosf`, `canon::sqrtf`,
`canon::expf`, `canon::logf`, `canon::powf`, `canon::tanf`,
`canon::asinf`, `canon::acosf`, `canon::atanf`, `canon::atan2f`,
`canon::sinhf`, `canon::coshf`, `canon::tanhf`, `canon::asinhf`,
`canon::acoshf`, `canon::atanhf`, `canon::cbrtf`, `canon::hypotf`,
`canon::expm1f`, and `canon::log1pf` are all real,
correctly-rounded, bit-exact implementations today — not a `<cmath>`
wrapper. All but sqrt/sqrtf are vendored from the
[CORE-MATH project](https://core-math.gitlabpages.inria.fr/) (MIT license,
see `third_party/core-math/`); sqrt/sqrtf are bit-exact for free since
IEEE754 mandates correctly-rounded hardware sqrt at both precisions.

The CI matrix (`.github/workflows/ci.yml`) runs a bit-exact digest job
across x86-64/ARM64 × GCC/Clang/clang-cl on every push and **fails the
build if any leg's output differs from any other's** — this is the actual
product claim being enforced, not just checked informationally.

Windows builds use clang-cl, not cl.exe: the vendored CORE-MATH sources
(`third_party/core-math/`) use GNU C extensions (`__attribute__`,
`__builtin_*`, `__int128`, inline asm) that cl.exe cannot parse at all.
clang-cl understands them and stays MSVC-ABI-compatible for linking against
the rest of the toolchain.

**v0.1 shipped six double-precision functions; v0.2 added seven more**
(`tan`/`asin`/`acos`/`atan`/`atan2`/`sinh`/`cosh`); **v0.3 added seven
more** (`tanh`/`asinh`/`acosh`/`atanh`/`cbrt`/`hypot`/`expm1`); **v0.4
added seven more** (`log1p`/`log2`/`log10`/`exp2`/`exp10`/`sincos`/
`rsqrt`); **v0.5 added seven more** (`erf`/`erfc`/`lgamma`/`tgamma`/
`sinpi`/`cospi`/`tanpi`); **v0.6 added seven more**
(`asinpi`/`acospi`/`atanpi`/`atan2pi`/`exp2m1`/`exp10m1`/`log2p1`); **v0.7
added `log10p1`**, closing out double precision entirely — 42 functions
real; **v0.8 started single precision** with `sinf`/`cosf`/`sqrtf`/
`expf`/`logf`/`powf`/`tanf` (49 functions real); **v0.9 added seven more**
(`asinf`/`acosf`/`atanf`/`atan2f`/`sinhf`/`coshf`/`tanhf`, 56 real);
**v0.10 adds seven more** (`asinhf`/`acoshf`/`atanhf`/`cbrtf`/`hypotf`/
`expm1f`/`log1pf`, 63 real). v1 is the full function-by-function target
list, with no exceptions carved out ahead of time: see
[docs/scope.md](docs/scope.md).

## Building

```bash
cmake -S . -B build -DCANON_SHARED=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

On Windows, configure with clang-cl (see Status above) rather than the
default MSVC toolset, e.g. from a Developer Command Prompt:

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
```

## C ABI

`include/canon/canon.h` exposes the scalar + hash surface for FFI.
Stability policy: [docs/abi-policy.md](docs/abi-policy.md).

## License

MIT — see [LICENSE](LICENSE).

## Security

See [SECURITY.md](SECURITY.md) for scope and misuse boundaries.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). This project follows the
[Contributor Covenant](CODE_OF_CONDUCT.md).

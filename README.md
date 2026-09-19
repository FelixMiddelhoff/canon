# isobit

Cross-platform bit-exact math library. Same input, same bits, every
platform.

## What this is

glibc, macOS's libm, MSVC's CRT and ARM's libm each implement
sin/cos/exp/log/pow slightly differently — usually within 1 ULP of the
correctly-rounded result, but not the *same* 1 ULP, and not on the same
inputs. That's invisible for most code and fatal for anything that needs
bit-exact reproducibility across machines: deterministic replay, lockstep
simulation, financial/scientific audit trails.

isobit replaces the platform-dependent subset of libm with a fixed,
correctly-rounded implementation, plus fixed-reduction-order vector/matrix
ops (SIMD-friendly reductions reorder summation, which also changes the
last bit).

```cpp
double a = isobit::sin(x);        // same 64 bits on x86-64, ARM64, any compiler
double d = isobit::dot(v1, v2, 3); // fixed left-to-right summation order
```

See `examples/` for runnable code: scalar math + `dot()`
(`quickstart.cpp`), `normalize()`/matrix `multiply()`
(`vecmat.cpp`), cross-node desync detection via `hash_bits()`
(`hash_determinism.cpp`), and the plain-C ABI (`c_abi.c`).

## Function coverage

Every function CORE-MATH provides a correctly-rounded implementation
for, at both double and single precision — the full list is in
[docs/scope.md](docs/scope.md). All of them (`isobit::sin`, `isobit::pow`,
`isobit::erff`, `isobit::atan2pif`, and everything else in that list) are
real, correctly-rounded, bit-exact implementations — not `<cmath>`
wrappers. All but `sqrt`/`sqrtf` are vendored from the
[CORE-MATH project](https://core-math.gitlabpages.inria.fr/) (MIT
license, see `third_party/core-math/`); `sqrt`/`sqrtf` are bit-exact for
free since IEEE754 mandates correctly-rounded hardware sqrt at both
precisions.

### Out of scope

Functions CORE-MATH doesn't cover because they're already exact via
hardware or trivial bit manipulation, not a correctly-rounding problem:
`floor`, `ceil`, `round`, `trunc`, `rint`, `nearbyint`, `modf`, `frexp`,
`ldexp`, `scalbn`, `ilogb`, `fmod`, `remainder`, `remquo`, `copysign`,
`nextafter`, `nexttoward`, `fmin`, `fmax`, `fdim`, `isnan`, `isinf`,
`isfinite`, `signbit`. Also out of scope: `long double`, f16/bf16,
complex-number math, and `fma` — correctly-rounded FMA is an
IEEE754-mandated hardware primitive where the target has one, but isobit
doesn't currently wrap it; use the compiler/hardware intrinsic directly
rather than assume isobit covers it. Full reasoning in
[docs/scope.md](docs/scope.md).

## Verification

The CI matrix (`.github/workflows/ci.yml`) runs a bit-exact digest job
across x86-64/ARM64 × GCC/Clang/clang-cl on every push and **fails the
build if any leg's output differs from any other's** — this is the actual
product claim being enforced, not just checked informationally. Every
function is also verified against a true correctly-rounded reference
(`mpmath` at high precision) before being considered done — `std::` and
platform `math` libraries are themselves only *usually* correctly-rounded,
so they're not a trustworthy check on their own.

Windows builds use clang-cl, not cl.exe: the vendored CORE-MATH sources
(`third_party/core-math/`) use GNU C extensions (`__attribute__`,
`__builtin_*`, `__int128`, inline asm, and the POSIX `signgam` global for
`lgamma`/`lgammaf`) that cl.exe cannot parse at all. clang-cl understands
them and stays MSVC-ABI-compatible for linking against the rest of the
toolchain.

## Installing prebuilt binaries

- **.NET**: `dotnet add package Isobit` — native binaries for win-x64,
  linux-x64, linux-arm64, and osx-arm64, resolved automatically per
  runtime identifier; `DllImport("isobit")` against the C ABI.
- **Anything else**: grab the platform zip (binary + `isobit.h` +
  `LICENSE`) from the [GitHub Releases](../../releases) page.

Both are built by [`.github/workflows/release.yml`](.github/workflows/release.yml)
from the same source every tagged release — no separately-maintained
build.

## Nuget

You can find it on https://www.nuget.org/packages/Isobit/

## Building from source

```bash
cmake -S . -B build -DISOBIT_SHARED=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

On Windows, configure with clang-cl (see Verification above) rather than
the default MSVC toolset, e.g. from a Developer Command Prompt:

```bash
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=clang-cl -DCMAKE_CXX_COMPILER=clang-cl
```

## C ABI

`include/isobit/isobit.h` exposes the scalar + hash surface for FFI.
Stability policy: [docs/abi-policy.md](docs/abi-policy.md).

## License

MIT — see [LICENSE](LICENSE).

## Security

See [SECURITY.md](SECURITY.md) for scope and misuse boundaries.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md). This project follows the
[Contributor Covenant](CODE_OF_CONDUCT.md).

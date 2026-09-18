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

`canon::sin`, `canon::cos`, `canon::exp`, `canon::log`, `canon::pow`, and
`canon::sqrt` are all real, correctly-rounded, bit-exact implementations
today — not a `<cmath>` wrapper. sin/cos/exp/log/pow are vendored from the
[CORE-MATH project](https://core-math.gitlabpages.inria.fr/) (MIT license,
see `third_party/core-math/`); sqrt is bit-exact for free since IEEE754
mandates correctly-rounded hardware sqrt.

The CI matrix (`.github/workflows/ci.yml`) runs a bit-exact digest job
across x86-64/ARM64 × GCC/Clang/clang-cl on every push and **fails the
build if any leg's output differs from any other's** — this is the actual
product claim being enforced, not just checked informationally.

Windows builds use clang-cl, not cl.exe: the vendored CORE-MATH sources
(`third_party/core-math/`) use GNU C extensions (`__attribute__`,
`__builtin_*`, `__int128`, inline asm) that cl.exe cannot parse at all.
clang-cl understands them and stays MSVC-ABI-compatible for linking against
the rest of the toolchain.

**v0.1 is six double-precision functions.** v1 is the full function-by-
function target list, with no exceptions carved out ahead of time: see
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

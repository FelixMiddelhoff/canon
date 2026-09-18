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

**`src/scalar.cpp` is currently a `<cmath>` wrapper**, i.e. exactly the
platform-divergent behavior canon exists to replace. It's there so the
skeleton builds and has a running test suite from day one. The CI matrix
(`.github/workflows/ci.yml`) already runs a bit-exact digest job across
x86-64/ARM64 × GCC/Clang/MSVC on every push — informational for now, it
becomes a hard pass/fail gate once the correctly-rounded implementation
lands.

`canon::sqrt` is the one function that's bit-exact *today* — IEEE754
mandates correctly-rounded hardware sqrt, so wrapping it needs no further
work.

## Building

```bash
cmake -S . -B build -DCANON_SHARED=ON
cmake --build build
ctest --test-dir build --output-on-failure
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

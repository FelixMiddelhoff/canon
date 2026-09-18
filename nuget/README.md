# Isobit

Cross-platform bit-exact math library. Same input, same bits, every
platform.

glibc, macOS's libm, MSVC's CRT and ARM's libm each implement
`sin`/`cos`/`exp`/`log`/`pow` slightly differently — usually within 1 ULP
of the correctly-rounded result, but not the *same* 1 ULP, and not on the
same inputs. Isobit replaces the platform-dependent subset of libm with a
fixed, correctly-rounded implementation (vendored from
[CORE-MATH](https://core-math.gitlabpages.inria.fr/), MIT license) that
produces identical output bits across x86-64/ARM64, on every OS, at
every optimization level.

This package ships native binaries (win-x64, linux-x64, linux-arm64,
osx-arm64) for the plain C ABI — call it via `DllImport`:

```csharp
using System.Runtime.InteropServices;

internal static class Isobit
{
    [DllImport("isobit")] public static extern double isobit_sin(double x);
    [DllImport("isobit")] public static extern double isobit_pow(double base_, double exponent);
    [DllImport("isobit")] public static extern ulong isobit_hash_bits(double[] values, nuint n);
}
```

.NET resolves the correct native binary for the current runtime
automatically from the package's `runtimes/<rid>/native/` folders — no
extra configuration needed as long as the consuming project has a
`RuntimeIdentifier` set (or is publishing self-contained).

78 functions total (36 `binary64` + 42 `binary32`), every one
correctly-rounded and CI-verified bit-identical across the full build
matrix. Full function list, C ABI reference, and source:
[github.com/FelixMiddelhoff/isobit](https://github.com/FelixMiddelhoff/isobit).

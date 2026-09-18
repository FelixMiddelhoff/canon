# Contributing to canon

## Building and testing

```bash
cmake -S . -B build -DCANON_SHARED=ON
cmake --build build
ctest --test-dir build --output-on-failure
```

Format before committing:

```bash
clang-format -i include/canon/*.hpp src/*.cpp tests/*.cpp examples/*.cpp
```

`.clang-format` and `.clang-tidy` at the repo root pin the style/lint rules;
most editors pick them up automatically.

## The property that must never regress

Bit-exactness across platforms is the entire product. Any change to
`src/scalar.cpp`, `src/vecmat.cpp`, or the compiler flags in
`CMakeLists.txt` (`-ffp-contract=off`, `/fp:strict`, etc.) needs the CI
bit-exact digest job (`.github/workflows/ci.yml`) checked across *all*
matrix legs, not just "it built on my machine." Never weaken those flags to
fix a build error without understanding why they were required in the
first place.

Do not add a new libm function without a `test_bitexact_golden.cpp` entry
for it.

## Submitting a pull request

1. Open an issue first for anything non-trivial (a new function, a change
   to the reduction order in `vecmat.cpp`, a new C ABI function) — cheap to
   discuss before code exists.
2. Keep PRs scoped to one change.
3. CI must pass (build matrix + sanitizers) before merge. A bit-exact
   digest mismatch across matrix legs is a real bug, not CI flakiness.
4. New public API (`include/canon/`) needs a test and a README update in
   the same PR — docs and code change together, not in a follow-up.

## Code of Conduct

This project follows the [Contributor Covenant](CODE_OF_CONDUCT.md).

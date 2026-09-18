# Security policy

## Reporting a vulnerability

Please **do not** open a public issue for a security vulnerability. Use
GitHub's private reporting instead:

1. Go to the [Security tab](https://github.com/FelixMiddelhoff/canon/security).
2. Click **Report a vulnerability**.
3. Describe the issue and, if possible, how to reproduce it.

## Supported versions

canon tracks a single moving line: the latest commit on `main`. There is
no older release branch receiving backports.

## Scope

canon is a pure math library: no network I/O, no file parsing, no dynamic
allocation in the core (`src/scalar.cpp`, `src/vecmat.cpp`, `src/hash.cpp`),
no dependencies. Realistic concerns:

- Out-of-bounds access on the `n`-length buffer arguments to `dot()` /
  `hash_bits()` — the API takes a raw pointer + length (matching the C ABI,
  `include/canon/canon.h`) and trusts the caller's length; this is
  documented, not a silent footgun the library should paper over with an
  exception (canon never throws — see below).
- The C ABI never letting a C++ exception cross into a C caller.
- Domain errors (`log` of a negative number, `pow` producing NaN/Inf,
  division by a zero-length `normalize()` vector) return NaN/Inf per
  IEEE754, matching `<cmath>` behavior — they do not throw or abort. Callers
  needing strict domain validation must check inputs themselves; canon's job
  is bit-exact math, not input sanitization.

## Misuse boundaries

- **canon makes a bit-exactness claim, not a correctness-under-adversarial-
  input claim.** It is not a hardened parser boundary and was never designed
  to sit directly on untrusted network input — validate/sanitize upstream of
  it the same way you would upstream of `<cmath>`.
- **`hash_bits()` is a checksum, not a cryptographic hash.** FNV-1a-style
  mixing over raw bit patterns, meant for desync/replay-divergence detection
  between trusted nodes running the same binary — never use it where an
  adversary could construct a colliding input (integrity/signing use cases
  need a real cryptographic hash instead).
- The bit-exactness claim is enforced by CI (`.github/workflows/ci.yml`'s
  `bitexact-verify` job fails the build on any cross-leg digest mismatch),
  not just asserted in prose — but it still only covers the functions in
  `tests/test_bitexact_golden.cpp` on the exact matrix legs CI runs. A
  platform/compiler/flag combination outside that matrix is unverified.

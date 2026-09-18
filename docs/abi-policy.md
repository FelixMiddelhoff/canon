# C ABI stability policy

`include/isobit/isobit.h` is the C ABI surface. Until `1.0.0`, it can break
between minor versions — every break must be called out in the release
notes. From `1.0.0` on:

- **Breaking** (major version bump): removing or renaming an exported
  function, changing a function's signature or return type, changing the
  precision guarantee of an existing function (e.g. a bug-fixed
  `isobit_sin` that now returns different bits for the same input is an ABI
  *and* a behavioral break — treat a correctness fix that changes output
  the same as a signature change for versioning purposes, since
  bit-exactness is the entire contract).
- **Non-breaking** (minor version bump): adding a new exported function.
- **Patch version**: reserved — isobit has no behavior-preserving-but-
  internal-only category of fix, because bit output *is* the ABI. If output
  bits change at all, it's at minimum a minor bump with a changelog entry.

No structs cross the C ABI by value yet (all functions are scalar
in/scalar out, or pointer+length). If that changes, layout stability for
any such struct is added to this policy before it ships, not after.

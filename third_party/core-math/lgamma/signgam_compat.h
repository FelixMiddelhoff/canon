#pragma once

// MSVC/clang-cl's <math.h> does not declare the POSIX/XSI `signgam` global
// that glibc/BSD libm provide and that this vendored lgamma.c reads/writes
// as a side effect. canon::lgamma never reads it back, so a local
// definition is enough — force-included ahead of lgamma.c only on the
// MSVC-family toolchain (see CMakeLists.txt), where the declaration is
// otherwise missing.
int signgam;

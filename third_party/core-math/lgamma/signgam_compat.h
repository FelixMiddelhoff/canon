#pragma once

// MSVC/clang-cl's <math.h> does not declare the POSIX/XSI `signgam` global
// that glibc/BSD libm provide and that lgamma.c/lgammaf.c read/write as a
// side effect. canon::lgamma/lgammaf never read it back, so a local
// definition is enough — force-included ahead of both files (see
// CMakeLists.txt), only on the MSVC-family toolchain, where the
// declaration is otherwise missing. `static` gives each translation unit
// its own copy so linking both files together doesn't collide on one
// external `signgam` symbol.
static int signgam;

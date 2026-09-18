# canon — cross-platform bit-exact math library.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(canon LANGUAGES C CXX VERSION 0.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Standalone build vs. consumed as a subdirectory.
set(CANON_STANDALONE OFF)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(CANON_STANDALONE ON)
endif()

option(CANON_SHARED         "Also build a shared library"  OFF)
option(CANON_BUILD_TESTS    "Build the test suite"         ${CANON_STANDALONE})
option(CANON_BUILD_BENCH    "Build the perf bench"         ${CANON_STANDALONE})
option(CANON_BUILD_EXAMPLES "Build the example programs"   ${CANON_STANDALONE})

set(CANON_SOURCES
  src/version.cpp
  src/scalar.cpp
  src/vecmat.cpp
  src/hash.cpp
  src/c_api.cpp
)

# Vendored CORE-MATH (MIT) correctly-rounded implementations. All five
# use GNU C extensions (__attribute__, __builtin_*, inline asm); log/pow
# additionally need __int128 for their accurate fallback path. Neither is
# available in cl.exe, hence the Windows CI leg uses clang-cl (see
# .github/workflows/ci.yml) rather than dropping MSVC support.
set(CANON_VENDOR_SOURCES
  third_party/core-math/sin/sin.c
  third_party/core-math/cos/cos.c
  third_party/core-math/exp/exp.c
  third_party/core-math/log/log.c
  third_party/core-math/pow/pow.c
  third_party/core-math/tan/tan.c
  third_party/core-math/asin/asin.c
  third_party/core-math/acos/acos.c
  third_party/core-math/atan/atan.c
  third_party/core-math/atan2/atan2.c
  third_party/core-math/sinh/sinh.c
  third_party/core-math/cosh/cosh.c
  third_party/core-math/tanh/tanh.c
  third_party/core-math/asinh/asinh.c
  third_party/core-math/acosh/acosh.c
  third_party/core-math/atanh/atanh.c
  third_party/core-math/cbrt/cbrt.c
  third_party/core-math/hypot/hypot.c
  third_party/core-math/expm1/expm1.c
  third_party/core-math/log1p/log1p.c
  third_party/core-math/log2/log2.c
  third_party/core-math/log10/log10.c
  third_party/core-math/exp2/exp2.c
  third_party/core-math/exp10/exp10.c
  third_party/core-math/sincos/sincos.c
  third_party/core-math/rsqrt/rsqrt.c
  third_party/core-math/erf/erf.c
  third_party/core-math/erfc/erfc.c
  third_party/core-math/lgamma/lgamma.c
  third_party/core-math/tgamma/tgamma.c
  third_party/core-math/sinpi/sinpi.c
  third_party/core-math/cospi/cospi.c
  third_party/core-math/tanpi/tanpi.c
  third_party/core-math/asinpi/asinpi.c
  third_party/core-math/acospi/acospi.c
  third_party/core-math/atanpi/atanpi.c
  third_party/core-math/atan2pi/atan2pi.c
  third_party/core-math/exp2m1/exp2m1.c
  third_party/core-math/exp10m1/exp10m1.c
  third_party/core-math/log2p1/log2p1.c
  third_party/core-math/log10p1/log10p1.c
  third_party/core-math/sinf/sinf.c
  third_party/core-math/cosf/cosf.c
  third_party/core-math/expf/expf.c
  third_party/core-math/logf/logf.c
  third_party/core-math/powf/powf.c
  third_party/core-math/tanf/tanf.c
  third_party/core-math/asinf/asinf.c
  third_party/core-math/acosf/acosf.c
  third_party/core-math/atanf/atanf.c
  third_party/core-math/atan2f/atan2f.c
  third_party/core-math/sinhf/sinhf.c
  third_party/core-math/coshf/coshf.c
  third_party/core-math/tanhf/tanhf.c
  third_party/core-math/asinhf/asinhf.c
  third_party/core-math/acoshf/acoshf.c
  third_party/core-math/atanhf/atanhf.c
  third_party/core-math/cbrtf/cbrtf.c
  third_party/core-math/hypotf/hypotf.c
  third_party/core-math/expm1f/expm1f.c
  third_party/core-math/log1pf/log1pf.c
)
add_library(canon_vendor OBJECT ${CANON_VENDOR_SOURCES})
set_target_properties(canon_vendor PROPERTIES POSITION_INDEPENDENT_CODE ON)
if(MSVC)
  target_compile_options(canon_vendor PRIVATE /fp:strict)
  # lgamma.c reads/writes the POSIX/XSI `signgam` global (glibc/BSD libm
  # declare it in <math.h>); MSVC/clang-cl's headers don't. canon::lgamma
  # never reads it back, so force-including a local definition ahead of
  # this one file is a real fix, not a workaround masking a bug.
  set_source_files_properties(third_party/core-math/lgamma/lgamma.c PROPERTIES
    COMPILE_OPTIONS "/FI${CMAKE_CURRENT_SOURCE_DIR}/third_party/core-math/lgamma/signgam_compat.h")
else()
  target_compile_options(canon_vendor PRIVATE
    -ffp-contract=off -fno-fast-math -frounding-math)
endif()

add_library(canon STATIC ${CANON_SOURCES} $<TARGET_OBJECTS:canon_vendor>)
add_library(canon::canon ALIAS canon)
target_include_directories(canon PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_compile_features(canon PUBLIC cxx_std_17)

# Bit-exactness is the entire point: never let the compiler contract
# multiply-add into FMA behind our back, never let it assume associative
# reordering of float ops. Both silently change the last bit(s).
if(MSVC)
  target_compile_options(canon PRIVATE /W4 /permissive- /fp:strict)
else()
  target_compile_options(canon PRIVATE -Wall -Wextra -Wpedantic
    -ffp-contract=off -fno-fast-math -frounding-math)
endif()

if(CANON_SHARED)
  add_library(canon_shared SHARED ${CANON_SOURCES} $<TARGET_OBJECTS:canon_vendor>)
  add_library(canon::shared ALIAS canon_shared)
  set_target_properties(canon_shared PROPERTIES OUTPUT_NAME canon)
  if(WIN32)
    # On Windows the shared lib's import library and the static lib both
    # want to be canon.lib in the same build tree — same extension, unlike
    # Unix's libcanon.so vs libcanon.a. Give the import lib a distinct name;
    # the DLL itself (RUNTIME_OUTPUT_NAME, unaffected here) still ends up
    # canon.dll.
    set_target_properties(canon_shared PROPERTIES ARCHIVE_OUTPUT_NAME canon_dll)
  endif()
  target_include_directories(canon_shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  target_compile_features(canon_shared PUBLIC cxx_std_17)
  if(MSVC)
    target_compile_options(canon_shared PRIVATE /fp:strict)
  else()
    target_compile_options(canon_shared PRIVATE -ffp-contract=off -fno-fast-math -frounding-math)
  endif()
  target_compile_definitions(canon_shared PRIVATE CANON_BUILD_SHARED PUBLIC CANON_SHARED)
endif()

if(CANON_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if(CANON_BUILD_BENCH)
  add_subdirectory(bench)
endif()

if(CANON_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

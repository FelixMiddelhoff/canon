# canon — cross-platform bit-exact math library.
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(canon LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

add_library(canon STATIC ${CANON_SOURCES})
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
  add_library(canon_shared SHARED ${CANON_SOURCES})
  add_library(canon::shared ALIAS canon_shared)
  set_target_properties(canon_shared PROPERTIES OUTPUT_NAME canon)
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

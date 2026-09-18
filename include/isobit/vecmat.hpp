#pragma once

#include <cstddef>

namespace isobit {

// Fixed left-to-right reduction order (never a tree/pairwise reduction, never
// SIMD-horizontal-add) so the result is identical regardless of vector width
// or compiler auto-vectorization decisions. That's the whole point: a
// mathematically equivalent but differently-ordered sum can differ in the
// last bit.
double dot(const double* a, const double* b, std::size_t n);

struct Vec3 {
  double x, y, z;
};

Vec3 normalize(Vec3 v);

struct Mat4 {
  double m[16];  // row-major
};

Mat4 multiply(const Mat4& a, const Mat4& b);

}  // namespace isobit

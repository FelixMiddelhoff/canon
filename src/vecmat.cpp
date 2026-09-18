#include "canon/vecmat.hpp"

#include "canon/scalar.hpp"

namespace canon {

double dot(const double* a, const double* b, std::size_t n) {
  double sum = 0.0;
  for (std::size_t i = 0; i < n; ++i) {
    sum += a[i] * b[i];  // fixed left-to-right order — see header comment
  }
  return sum;
}

Vec3 normalize(Vec3 v) {
  const double len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  return Vec3{v.x / len, v.y / len, v.z / len};
}

Mat4 multiply(const Mat4& a, const Mat4& b) {
  Mat4 out{};
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      double sum = 0.0;
      for (int k = 0; k < 4; ++k) {
        sum += a.m[row * 4 + k] * b.m[k * 4 + col];
      }
      out.m[row * 4 + col] = sum;
    }
  }
  return out;
}

}  // namespace canon

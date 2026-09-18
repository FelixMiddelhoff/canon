#include <cassert>
#include <cmath>
#include <cstdio>

#include "isobit/vecmat.hpp"

int main() {
  const double a[3] = {1.0, 2.0, 3.0};
  const double b[3] = {4.0, 5.0, 6.0};
  assert(isobit::dot(a, b, 3) == 32.0);

  isobit::Vec3 v = isobit::normalize(isobit::Vec3{3.0, 0.0, 4.0});
  assert(std::abs(v.x - 0.6) < 1e-15);
  assert(std::abs(v.z - 0.8) < 1e-15);

  isobit::Mat4 id{};
  for (int i = 0; i < 4; ++i) id.m[i * 4 + i] = 1.0;
  isobit::Mat4 r = isobit::multiply(id, id);
  for (int i = 0; i < 16; ++i) assert(r.m[i] == id.m[i]);

  std::puts("test_vecmat: ok");
  return 0;
}

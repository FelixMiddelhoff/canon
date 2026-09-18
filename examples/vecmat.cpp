#include <cstdio>

#include "isobit/vecmat.hpp"

int main() {
  isobit::Vec3 v = isobit::normalize({3.0, 4.0, 12.0});
  std::printf("normalize(3,4,12) = (%.17f, %.17f, %.17f)\n", v.x, v.y, v.z);

  isobit::Mat4 identity{{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1}};
  isobit::Mat4 scale{{2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 1}};
  isobit::Mat4 r = isobit::multiply(identity, scale);
  std::printf("identity * scale(2) diagonal = %.1f %.1f %.1f %.1f\n", r.m[0],
              r.m[5], r.m[10], r.m[15]);

  return 0;
}

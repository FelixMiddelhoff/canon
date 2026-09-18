#include <cstdio>

#include "isobit/scalar.hpp"
#include "isobit/vecmat.hpp"

int main() {
  const double a[3] = {1.0, 2.0, 3.0};
  const double b[3] = {4.0, 5.0, 6.0};
  std::printf("dot = %f\n", isobit::dot(a, b, 3));
  std::printf("sqrt(2) = %.17f\n", isobit::sqrt(2.0));
  return 0;
}

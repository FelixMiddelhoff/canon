// Prints the raw bit pattern (as hex) of a fixed set of scalar.hpp calls.
// CI runs this on every OS/compiler leg in the matrix and diffs the logs —
// see .github/workflows/ci.yml "Cross-platform bit-exact digest". A mismatch
// here is the signal that scalar.cpp's <cmath> placeholder needs to become
// the real correctly-rounded implementation for that function.
#include <cstdint>
#include <cstdio>
#include <cstring>

#include "canon/scalar.hpp"

namespace {

void print_bits(const char* label, double v) {
  std::uint64_t bits;
  std::memcpy(&bits, &v, sizeof(bits));
  std::printf("%s: %016llx\n", label, static_cast<unsigned long long>(bits));
}

}  // namespace

int main() {
  print_bits("sin(1.0)", canon::sin(1.0));
  print_bits("cos(1.0)", canon::cos(1.0));
  print_bits("exp(1.0)", canon::exp(1.0));
  print_bits("log(2.0)", canon::log(2.0));
  print_bits("pow(1.0001,1000.0)", canon::pow(1.0001, 1000.0));
  print_bits("sqrt(2.0)", canon::sqrt(2.0));
  return 0;
}

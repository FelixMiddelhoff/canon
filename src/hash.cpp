#include "isobit/hash.hpp"

#include <cstring>

namespace isobit {

namespace {

std::uint64_t mix(std::uint64_t h, std::uint64_t v) noexcept {
  // FNV-1a-style mix over raw bit patterns — deterministic given identical
  // input bits, which is the only guarantee this function needs to make.
  h ^= v;
  h *= 0x100000001B3ULL;
  return h;
}

}  // namespace

std::uint64_t hash_bits(const double* values, std::size_t n) {
  std::uint64_t h = 0xCBF29CE484222325ULL;
  for (std::size_t i = 0; i < n; ++i) {
    std::uint64_t bits;
    std::memcpy(&bits, &values[i], sizeof(bits));
    h = mix(h, bits);
  }
  return h;
}

}  // namespace isobit

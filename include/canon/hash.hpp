#pragma once

#include <cstddef>
#include <cstdint>

namespace canon {

// Canonical bit-level checksum of a float buffer — for cross-platform
// desync detection (e.g. comparing two ravel/foldback nodes' state without
// shipping the full buffer). Hashes the raw IEEE754 bit pattern, so two
// buffers that are bit-identical per canon's guarantees hash identically;
// this is NOT a hash with any tolerance for near-equal floats.
std::uint64_t hash_bits(const double* values, std::size_t n);

}  // namespace canon

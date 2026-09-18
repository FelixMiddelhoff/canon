// The actual use case hash_bits() exists for: two nodes running a lockstep
// simulation (or a replay vs. its original recording) exchange a cheap
// checksum instead of the full state buffer, and compare. Because every
// isobit:: function is bit-exact across platforms/compilers, a mismatch
// here means real state divergence, not floating-point noise from a
// differently-ordered reduction or a 1-ULP libm difference.
#include <cstdio>

#include "isobit/hash.hpp"
#include "isobit/scalar.hpp"
#include "isobit/vecmat.hpp"

namespace {

// Stand-in for one simulation tick: some bit-exact math producing a small
// state buffer. In a real lockstep sim this would be entity positions,
// velocities, etc. after this tick's integration step.
void simulate_tick(double state[4], double dt) {
  state[0] = isobit::sin(state[0] + dt);
  state[1] = isobit::cos(state[1] + dt);
  state[2] = isobit::sqrt(state[2] + dt);
  state[3] = isobit::dot(state, state, 3);
}

}  // namespace

int main() {
  double state[4] = {0.1, 0.2, 1.0, 0.0};
  for (int tick = 0; tick < 100; ++tick) {
    simulate_tick(state, 0.016);
  }

  std::uint64_t checksum = isobit::hash_bits(state, 4);
  std::printf("state after 100 ticks: checksum = %016llx\n",
              static_cast<unsigned long long>(checksum));
  std::printf(
      "This checksum is bit-exact across every platform in the CI matrix — "
      "a peer node computing the same 100 ticks should print the exact same "
      "value. A mismatch means real divergence, not floating-point noise.\n");

  return 0;
}

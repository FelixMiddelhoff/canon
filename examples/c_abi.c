/* Plain C, proving the C ABI (include/isobit/isobit.h) works without a C++
 * toolchain on the consumer side — the whole point of exposing one, for
 * FFI from other languages/engines. */
#include <stdio.h>

#include "isobit/isobit.h"

int main(void) {
  double values[3];
  values[0] = isobit_sin(1.0);
  values[1] = isobit_cos(1.0);
  values[2] = isobit_sqrt(2.0);

  printf("isobit_sin(1.0)  = %.17g\n", values[0]);
  printf("isobit_cos(1.0)  = %.17g\n", values[1]);
  printf("isobit_sqrt(2.0) = %.17g\n", values[2]);
  printf("isobit_hash_bits = %016llx\n",
         (unsigned long long)isobit_hash_bits(values, 3));
  printf("isobit version   = %s\n", isobit_version_string());

  return 0;
}

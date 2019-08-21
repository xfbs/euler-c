#include "solve.h"

uint64_t solve(uint64_t max, uint64_t digits) {
  uint64_t mod = pow(10, digits);
  uint64_t series[max];

  for (size_t num = 0; num < max; num++) {
    series[num] = pow_mod(num + 1, num + 1, mod);
  }

  return sum_mod(series, max, mod);
}

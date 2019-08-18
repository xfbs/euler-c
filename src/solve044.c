#include "solve.h"
#include <math.h>
#include <stddef.h>
#include <stdio.h>

uint64_t p(uint64_t x) { return x * (3 * x - 1) / 2; }

uint64_t p_inverse(uint64_t _y) {
  double y = _y;

  return (uint64_t)((1.0 / 6.0) + sqrt(pow(1.0 / 6.0, 2) - (-2.0 / 3.0) * y) +
                    0.5);
}

bool is_p(uint64_t x) { return p(p_inverse(x)) == x; }

uint64_t b(uint64_t n) { return (3 * n * n + 5 * n) / 2; }

uint64_t solve() {
  for (uint64_t i = 1;; i++) {
    // calculate p(i)
    uint64_t p_i = p(i);

    // assuming that p(i) = p(x + n) - p(x), find possible [x, n] pairs
    for (uint64_t n = 1; b(n) <= p_i; n++) {
      // p(x + n) - p(x) = b(n) + 3n(x-1)
      if (((p_i - b(n)) % (3 * n)) == 0) {
        // find the value of x
        uint64_t x = (p_i - b(n)) / (3 * n) + 1;

        if (is_p(p(x) + p(x + n))) {
          return p_i;
        }
      }
    }
  }

  return 0;
}

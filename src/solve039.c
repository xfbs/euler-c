#include "solve.h"

uint32_t solve(uint32_t max) {
  uint32_t res = 0;
  uint32_t val = 0;

  for (uint32_t p = 1; p <= max; p++) {
    uint32_t cur = solutions_count(p);

    if (cur > val) {
      val = cur;
      res = p;
    }
  }

  return res;
}

uint32_t solutions_count(int32_t p) {
  uint32_t count = 0;

  for (int32_t a = 1; a < (p / 3); a++) {
    if ((p * (2 * a - p)) % (2 * (a - p)) == 0) {
      count += 1;
    }
  }

  return count;
}

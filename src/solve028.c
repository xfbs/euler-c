#include "solve.h"

uint64_t solve(uint64_t max) {
  uint64_t sum = 1;
  uint64_t cur = 1;

  for (uint64_t ring = 2; ring < max; ring += 2) {
    cur += ring;
    sum += cur;
    cur += ring;
    sum += cur;
    cur += ring;
    sum += cur;
    cur += ring;
    sum += cur;
  }

  return sum;
}

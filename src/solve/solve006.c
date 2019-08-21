#include "solve.h"

uint32_t solve(uint32_t n) {
  uint32_t n2 = n * n;
  uint32_t n3 = n2 * n;
  uint32_t n4 = n2 * n2;
  return (3 * n4 + 2 * n3 - 3 * n2 - 2 * n) / 12;
}

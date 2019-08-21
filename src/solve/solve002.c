#include "solve.h"
#include <euler/math.h>

uint64_t solve(uint64_t max) {
  uint64_t sum = 0;

  for(uint32_t cur = 2; fibonacci(cur) < max; cur += 3) {
    sum += fibonacci(cur);
  }

  return sum;
}

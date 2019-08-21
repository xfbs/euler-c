#include "solve.h"
#include <euler/math.h>
#include <euler/prime.h>
#include <stdbool.h>

uint32_t solve(size_t max) {
  bool pairs[max];

  // set all to false
  for(size_t pos = 0; pos < max; pos++) {
    pairs[pos] = false;
  }

  for (size_t i = 1; i < max; i++) {
    if (!pairs[i]) {
      uint32_t pair = amicable_pair(i);

      if (pair) {
        pairs[pair] = true;
        pairs[i] = true;
      }
    }
  }

  uint32_t sum = 0;
  for (size_t i = 1; i < max; i++) {
    if (pairs[i]) {
      sum += i;
    }
  }

  return sum;
}

uint32_t amicable_pair(uint32_t num) {
  uint32_t pair = divisor_sum(num);

  if (num != pair && num == divisor_sum(pair)) {
    return pair;
  } else {
    return 0;
  }
}

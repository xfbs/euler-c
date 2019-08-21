#include "solve.h"
#include <euler/math.h>
#include <stdbool.h>

uint32_t solve(size_t max) {
  uint8_t possible[max];
  for (size_t i = 0; i < max; i++)
    possible[i] = false;

  // list of abundant numbers up to max
  uint32_t abundant[max];
  size_t abundant_pos = 0;

  for (size_t i = 1; i < max; i++) {
    if (divisor_sum(i) > i) {
      abundant[abundant_pos] = i;
      abundant_pos++;
    }
  }

  // mark every sum of two abundant numbers as possible
  for (size_t a = 0; a < abundant_pos; a++) {
    for (size_t b = a; b < abundant_pos; b++) {
      uint32_t sum = abundant[a] + abundant[b];
      if (sum >= max)
        break;
      possible[sum] = true;
    }
  }

  // get the sum of all numbers which cannot be expressed as the sum of two
  // abundant numbers
  uint32_t sum = 0;
  for (size_t i = 0; i < max; i++) {
    if (!possible[i]) {
      sum += i;
    }
  }

  return sum;
}

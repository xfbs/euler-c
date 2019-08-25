#include "solve023.h"
#include <euler/math.h>
#include <stdbool.h>

uint32_t non_abundant_sums(size_t max) {
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

struct euler_result solve023(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input023, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", non_abundant_sums(max));

  return result;
}

const struct euler_input input023[] = {
  euler_input_number(max, "maximum number to check.", 28123, 0, INT64_MAX),
  {NULL},
};

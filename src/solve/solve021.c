#include "solve021.h"
#include <euler/math.h>
#include <euler/prime.h>
#include <stdbool.h>

uint32_t amicable_numbers(size_t max) {
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

struct euler_result solve021(json_t *input) {
  struct euler_result result;
  int64_t limit;

  result = euler_input_get(input021, input, &limit);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", amicable_numbers(limit));

  return result;
}

const struct euler_input input021[] = {
  euler_input_number(limit, "maximum for amicable numbers.", 10000, 0, INT64_MAX),
  {NULL},
};

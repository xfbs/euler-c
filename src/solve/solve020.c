#include "solve020.h"
#include <euler/vec16.h>

uint64_t factorial_digit_sum(uint32_t exp) {
  vec16_t num = vec16_new(1, 1);

  // compute exp!
  for (uint32_t f = 1; f <= exp; f++) {
    uint16_t carry = 0;
    for (size_t i = 0; i < vec16_len(&num); i++) {
      uint32_t cur = f * (uint32_t)vec16_get(&num, i) + carry;
      vec16_set(&num, i, cur % 10000);
      carry = cur / 10000;
    }

    if (carry != 0) {
      vec16_push(&num, carry);
    }
  }

  // compute sum of digits
  uint64_t sum = 0;
  for (size_t i = 0; i < vec16_len(&num); i++) {
    int pos = 1;
    for (size_t d = 0; d < 4; d++) {
      sum += (vec16_get(&num, i) / pos) % 10;
      pos *= 10;
    }
  }

  return sum;
}

struct euler_result solve020(json_t *input) {
  struct euler_result result;
  int64_t factorial;

  result = euler_input_get(input020, input, &factorial);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", factorial_digit_sum(factorial));

  return result;
}

const struct euler_input input020[] = {
  euler_input_number(factorial, "factorial of which to sum the digits.", 100, 0, INT64_MAX),
  {NULL},
};

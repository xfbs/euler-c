#include "solve016.h"
#include <euler/vec8.h>

uint64_t power_digit_sum(size_t exp) {
  vec8_t num = vec8_new(1, 1);

  // compute 2^exp
  for (size_t i = 0; i < exp; i++) {
    uint8_t carry = 0;
    for (size_t i = 0; i < vec8_len(&num); i++) {
      uint8_t cur = vec8_get(&num, i);
      cur *= 2;
      cur += carry;
      vec8_set(&num, i, cur % 10);
      carry = cur / 10;
    }

    if (carry != 0) {
      vec8_push(&num, carry);
    }
  }

  // compute sum of digits
  uint64_t sum = 0;
  for (size_t i = 0; i < vec8_len(&num); i++) {
    sum += vec8_get(&num, i);
  }

  return sum;
}

struct euler_result solve016(json_t *input) {
  struct euler_result result;
  int64_t exponent;

  result = euler_input_get(input016, input, &exponent);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", power_digit_sum(exponent));

  return result;
}

const struct euler_input input016[] = {
  euler_input_number(exponent, "exponent of 2 for which to sum digits", 1000, 0, INT64_MAX),
  {NULL},
};

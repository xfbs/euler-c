#include "solve004.h"
#include <euler/math.h>
#include <math.h>

uint32_t largest_palindrome_product(uint32_t digits) {
  uint32_t min = pow(10, digits - 1);
  uint32_t max = pow(10, digits);
  uint32_t match = 0;

  for (uint32_t first = min; first < max; first++) {
    for (uint32_t second = first; second < max; second++) {
      uint32_t product = first * second;
      if (product > match && is_palindrome(product)) {
        match = product;
      }
    }
  }

  return match;
}

struct euler_result solve004(json_t *input) {
  struct euler_result result;
  int64_t digits;

  result = euler_input_get(input004, input, &digits);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", largest_palindrome_product(digits));

  return result;
}

const struct euler_input input004[] = {
  euler_input_number(digits, "Number of digits", 3, 1, UINT32_MAX),
  {NULL},
};

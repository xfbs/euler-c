#include "solve025.h"
#include <math.h>

uint32_t n_digit_fibonacci_number(uint32_t max) {
  double phi = (1.0 + sqrt(5)) / 2;

  double sum1 = 0.5 * log(5);
  double sum2 = (max - 1) * log(10);
  return ceil((sum1 + sum2) / log(phi));
}

struct euler_result solve025(json_t *input) {
  struct euler_result result;
  int64_t digits;

  result = euler_input_get(input025, input, &digits);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", n_digit_fibonacci_number(digits));

  return result;
}

const struct euler_input input025[] = {
  euler_input_number(max, "maximum number to check.", 1000, 0, INT64_MAX),
  {NULL},
};

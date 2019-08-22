#include "solve002.h"
#include <euler/math.h>
#include <euler/common.h>

uint64_t even_fibonacci_numbers(uint64_t max) {
  uint64_t sum = 0;

  for(uint32_t cur = 2; fibonacci(cur) < max; cur += 3) {
    sum += fibonacci(cur);
  }

  return sum;
}

struct euler_result solve002(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input002, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%u", even_fibonacci_numbers(max));
  return result;
}

const struct euler_input input002[] = {
  euler_input_number(max, "maximum", 4000000, 0, INT64_MAX),
  {NULL},
};

#include "solve001.h"
#include <euler/math.h>
#include <stdio.h>

uint32_t sum_multiples(uint32_t max, uint32_t div1, uint32_t div2) {
  return sum_divisible(max, div1) + sum_divisible(max, div2) -
         sum_divisible(max, lcm(div1, div2));
}

uint32_t sum_divisible(uint32_t max, uint32_t divisor) {
  // smallest number lower than max that is
  // divisible by divisor
  int bound = max - (max % divisor);

  return (bound * ((bound / divisor) + 1)) / 2;
}

struct euler_result solve001(const struct euler_input *input) {
  struct euler_result result;

  uint32_t max = euler_input_get_number(input, "max", &result);
  if(!result.ok) return result;
  uint32_t a = euler_input_get_number(input, "a", &result);
  if(!result.ok) return result;
  uint32_t b = euler_input_get_number(input, "b", &result);
  if(!result.ok) return result;

  euler_write(&result, "%u", sum_multiples(max, a, b));
  return result;
}

const struct euler_input input001[] = {
  euler_input_number(max, "Number", 999),
  euler_input_number(a, "Number", 3),
  euler_input_number(b, "Number", 5),
  {NULL},
};

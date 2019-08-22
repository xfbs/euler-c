#include "solve005.h"
#include <euler/math.h>

uint32_t smallest_multiple(uint32_t max) {
  uint32_t l = 1;

  for (uint32_t i = 2; i <= max; i++) {
    l = lcm(l, i);
  }

  return l;
}

struct euler_result solve005(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input005, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%u", smallest_multiple(max));
  return result;
}

const struct euler_input input005[] = {
  euler_input_number(max, "max", 20, 1, INT64_MAX),
  {NULL},
};

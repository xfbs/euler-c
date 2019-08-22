#include "solve005.h"
#include <euler/math.h>

uint32_t smallest_multiple(uint32_t max) {
  uint32_t l = 1;

  for (uint32_t i = 2; i <= max; i++) {
    l = lcm(l, i);
  }

  return l;
}

struct euler_result solve005(const struct euler_input *input) {
  struct euler_result result;

  uint64_t max = euler_input_get_number(input, "max", &result);
  if(!result.ok) return result;

  euler_write(&result, "%u", smallest_multiple(max));
  return result;
}

const struct euler_input input005[] = {
  euler_input_number(max, "max", 20, 1, INT64_MAX),
  {NULL},
};

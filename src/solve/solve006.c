#include "solve006.h"

uint32_t sum_square_difference(uint32_t n) {
  uint32_t n2 = n * n;
  uint32_t n3 = n2 * n;
  uint32_t n4 = n2 * n2;
  return (3 * n4 + 2 * n3 - 3 * n2 - 2 * n) / 12;
}

struct euler_result solve006(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input006, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", sum_square_difference(max));

  return result;
}

const struct euler_input input006[] = {
  euler_input_number(max, "max", 100, 0, UINT32_MAX),
  {NULL},
};

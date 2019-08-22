#include "solve009.h"

uint32_t special_pythagoran_triplet(uint32_t n) {
  for (uint32_t c = (n - 3) / 3; c < (n - 1); c++) {
    for (uint32_t b = (n - c - 1) / 2; (c < n - c) ? (b < c) : (b < (n - c));
         b++) {
      uint32_t a = n - c - b;
      if (is_pythagorean_triplet(a, b, c)) {
        return a * b * c;
      }
    }
  }

  return 0;
}

bool is_pythagorean_triplet(uint32_t a, uint32_t b, uint32_t c) {
  if (a > b)
    return false;
  if (b > c)
    return false;
  if ((a * a + b * b) != (c * c))
    return false;
  return true;
}

struct euler_result solve009(json_t *input) {
  struct euler_result result;
  int64_t sum;

  result = euler_input_get(input009, input, &sum);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", special_pythagoran_triplet(sum));

  return result;
}

const struct euler_input input009[] = {
  euler_input_number(sum, "sum of pythagorean triplet", 1000, 0, UINT32_MAX),
  {NULL},
};

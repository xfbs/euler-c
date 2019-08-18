#include "solve.h"
#include <stddef.h>
#include <stdio.h>
#include <euler/vec.h>

uint64_t solve(vecp_t *numbers) {
  uint64_t sum = 0;

  for (size_t i = 0; i < vec_len(numbers); i++) {
    uint64_t cur = 0;
    sscanf(vec_get(numbers, i), "%11llu", &cur);
    sum += cur;
  }

  while (sum > 9999999999LL) {
    sum /= 10;
  }

  return sum;
}

#include "solve.h"
#include <euler/vec.h>
#include <string.h>

uint64_t weight(const char *str) {
  uint64_t w = 0;
  for (size_t i = 0; str[i]; i++) {
    w += str[i] - 'A' + 1;
  }

  return w;
}

uint64_t solve(vecp_t *v) {
  vec_sort(v, (vecp_cmp) strcmp);

  uint64_t sum = 0;
  for (size_t i = 0; i < vec_len(v); i++) {
    sum += (i + 1) * weight(vec_get(v, i));
  }

  return sum;
}

#include "solve.h"
#include <math.h>
#include <stdio.h>
#include <euler/vec.h>

uint64_t solve(vecp_t *v) {
  uint64_t sum = 0;

  for (size_t i = 0; i < vec_len(v); i++) {
    if (is_triangle_word(vec_get(v, i))) {
      sum += 1;
    }
  }

  return sum;
}

uint64_t weight(const char *str) {
  uint64_t w = 0;
  for (size_t i = 0; str[i]; i++) {
    w += str[i] - 'A' + 1;
  }

  return w;
}

bool is_triangle_word(const char *word) {
  uint64_t w = weight(word);
  return is_triangle_number(w);
}

bool is_triangle_number(uint64_t num) {
  // calculate inverse
  uint64_t x = sqrt(2 * num);
  return num == ((x * (x + 1)) / 2);
}

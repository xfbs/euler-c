#include "solve.h"

uint64_t solve(vec8_t *v, size_t len) {
  // find sequence of contiguous, non-zero numbers of length len
  size_t run = 0;
  size_t start = vec8_len(v);
  for (size_t i = 0; i < vec8_len(v); i++) {
    if (vec8_get(v, i) != 0) {
      run++;
    }

    if (run == len) {
      start = run - len;
      break;
    }
  }

  // make sure we have a valid starting point
  if (start == vec8_len(v))
    return 0;

  // find the initial product
  uint64_t max, product = 1;
  for (size_t i = start; i < (start + len); i++) {
    product *= vec8_get(v, i);
  }

  // set initial max to initial product
  max = product;

  // go through the rest of the vec
  size_t last_zero = 0;
  for (size_t i = start + len; i < vec8_len(v); i++) {
    if (last_zero)
      last_zero--;
    if (vec8_get(v, i) == 0) {
      last_zero = len;
    } else {
      product *= vec8_get(v, i);
    }

    if (vec8_get(v, i - len)) {
      product /= vec8_get(v, i - len);
    }

    if (!last_zero && product > max) {
      max = product;
    }
  }

  return max;
}

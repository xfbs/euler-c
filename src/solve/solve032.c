#include "solve.h"
#include <euler/vec16.h>
#include <stdbool.h>
#include <stdlib.h>

uint32_t solve() {
  vec16_t products = vec16_new(0, 0);

  for (uint32_t a = 1; a < 99; a++) {
    for (uint32_t b = a; b < 9999; b++) {
      uint32_t p = pandigital_product(a, b);
      if (p != 0) {
        if (SIZE_MAX == vec16_index(&products, p)) {
          vec16_push(&products, p);
        }
      }
    }
  }

  return vec16_sum(&products);
}

static inline bool check_digits(bool digits[10], uint32_t num) {
  for (; num > 0; num /= 10) {
    if (digits[num % 10])
      return false;
    digits[num % 10] = true;
  }

  return true;
}

uint32_t pandigital_product(uint32_t a, uint32_t b) {
  bool digits[10] = {false};
  uint32_t p = a * b;

  if (!check_digits(digits, a) || !check_digits(digits, b) ||
      !check_digits(digits, p)) {
    return 0;
  }

  for (size_t digit = 0; digit < 10; digit++) {
    if (digits[digit] == (digit == 0)) {
      return 0;
    }
  }

  return p;
}

#include "solve.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

uint64_t solve() {
  for (uint64_t exp = 100;; exp *= 10) {
    uint64_t max = (10 * exp) / 6;
    for (uint64_t num = exp; num <= max; num++) {
      if (is_permuted_multiple(num)) {
        return num;
      }
    }
  }

  return 0;
}

int cmp_uint8(const void *_a, const void *_b) {
  const uint8_t *a = _a;
  const uint8_t *b = _b;
  if (*a == *b)
    return 0;
  if (*a < *b)
    return -1;
  return 1;
}

bool is_permuted_multiple(uint64_t x) {
  digits_t digits[5];

  // generate digits
  for (size_t i = 0; i < 5; i++) {
    digits[i] = num_to_digits((i + 2) * x);
  }

  // make sure all numbers have the same amount of digits
  for (size_t i = 1; i < 5; i++) {
    if (digits[0].count != digits[i].count) {
      return false;
    }
  }

  // sort the first number's digits
  qsort(&digits[0].digits[0], digits[0].count, sizeof(digits[0].digits[0]),
        &cmp_uint8);

  // make sure all digits are same
  for (size_t i = 1; i < 5; i++) {
    // sort the ith number's digits
    qsort(&digits[i].digits[0], digits[i].count, sizeof(digits[i].digits[0]),
          &cmp_uint8);

    // compare to first number
    if (0 != memcmp(&digits[0].digits[0], &digits[i].digits[0],
                    digits[0].count * sizeof(digits[0].digits[0]))) {
      return false;
    }
  }

  return true;
}

digits_t num_to_digits(uint64_t n) {
  digits_t d = {0, {0}};

  while (n != 0) {
    d.digits[d.count] = n % 10;
    d.count++;
    n /= 10;
  }

  return d;
}

#include "solve.h"

uint32_t solve(size_t max) {
  uint32_t triangle = 1;
  uint32_t index = 1;
  prime_t p = prime_new();

  while (factor_count(&p, triangle) < max) {
    index++;
    triangle += index;
  }

  return triangle;
}

uint32_t factor_count(prime_t *p, uint32_t num) {
  uint32_t count = 1;

  for (size_t i = 0; num != 1; i++) {
    uint32_t factors = 1;
    uint32_t prime = prime_nth(p, i);

    while ((num % prime) == 0) {
      factors++;
      num /= prime;
    }

    count *= factors;
  }

  return count;
}

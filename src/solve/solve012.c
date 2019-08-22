#include "solve012.h"

uint32_t highly_divisible_triangular(size_t max) {
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

struct euler_result solve012(json_t *input) {
  struct euler_result result;
  int64_t divisors;

  result = euler_input_get(input012, input, &divisors);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", highly_divisible_triangular(divisors));

  return result;
}

const struct euler_input input012[] = {
  euler_input_number(divisors, "number of divisors", 500, 0, INT64_MAX),
  {NULL},
};

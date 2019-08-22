#include "solve010.h"
#include <euler/sieve.h>

uint64_t summation_of_primes(uint64_t max) {
  sieve_t sieve = sieve_new(max);
  uint64_t sum = 0;

  for (uint64_t num = 0; num < max; num++) {
    if (sieve_check(&sieve, num)) {
      sum += num;
    }
  }

  sieve_free(&sieve);
  return sum;
}

struct euler_result solve010(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input010, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", summation_of_primes(max));

  return result;
}

const struct euler_input input010[] = {
  euler_input_number(max, "maximum", 2000000, 0, INT64_MAX),
  {NULL},
};

#include "solve007.h"
#include <euler/prime.h>

uint64_t nth_prime(uint32_t pos) {
  prime_t p = prime_new();

  // generate nth prime (subtract pos by one because prime_nth is
  // zero-indexed)
  uint64_t prime = prime_nth(&p, pos - 1);

  prime_free(&p);

  return prime;
}

struct euler_result solve007(json_t *input) {
  struct euler_result result;
  int64_t nth;

  result = euler_input_get(input007, input, &nth);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", nth_prime(nth));

  return result;
}

const struct euler_input input007[] = {
  euler_input_number(nth, "nth prime to generate", 10001, 1, UINT32_MAX),
  {NULL},
};

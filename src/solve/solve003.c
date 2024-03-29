#include "solve003.h"
#include <euler/prime.h>

uint64_t largest_prime_factor(uint64_t num) {
  prime_t primes = prime_new();

  uint64_t cur = 2;
  while (!prime_check(&primes, num)) {
    if ((num % cur) == 0) {
      num /= cur;
    } else {
      do {
        cur += 1;
      } while (!prime_check(&primes, cur));
    }
  }

  return num;
}

struct euler_result solve003(json_t *input) {
  struct euler_result result;
  int64_t number;

  result = euler_input_get(input003, input, &number);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", largest_prime_factor(number));

  return result;
}

const struct euler_input input003[] = {
  euler_input_number(number, "Number of which to get the largest prime factor.", 600851475143, 2, INT64_MAX
 ),
  {NULL},
};

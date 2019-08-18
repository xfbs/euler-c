#include "solve.h"

uint32_t solve(size_t max) {
  prime_t p = prime_new();
  uint32_t sum = 0;

  // we start with the fourth prime, which is 11, because primes below 10 are
  // not considered truncatable.
  for (size_t i = 4; max; i++) {
    uint32_t prime = prime_nth(&p, i);
    if (truncatable(&p, prime)) {
      sum += prime;
      max--;
    }
  }

  return sum;
}

bool truncatable(prime_t *p, uint32_t prime) {
  uint32_t cur = prime / 10;
  uint32_t exp = 10;

  while (cur > 0) {
    if (prime_which(p, cur) == SIZE_MAX)
      return false;
    if (prime_which(p, prime % exp) == SIZE_MAX)
      return false;
    exp *= 10;
    cur /= 10;
  }

  return true;
}

#include "solve.h"
#include <euler/sieve.h>

uint64_t solve(uint64_t max) {
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

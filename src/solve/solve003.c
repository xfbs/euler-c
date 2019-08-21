#include "solve.h"
#include <math.h>
#include <euler/prime.h>

uint64_t solve(uint64_t num) {
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

#include "solve.h"

uint32_t solve(size_t max) {
  // generate all primes below max
  prime_t p = prime_new();
  size_t primes = prime_below(&p, max);

  // initialize array to keep track which primes are cyclic
  bool cyclic[primes];
  for(size_t pos = 0; pos < primes; pos++) {
    cyclic[pos] = false;
  }

  for (size_t i = 0; i < primes; i++) {
    check_prime_cycle(&p, cyclic, i);
  }

  // count all cyclic primes and return result
  uint32_t count = 0;
  for(size_t pos = 0; pos < primes; pos++) {
    if(cyclic[pos]) {
      count += 1;
    }
  }

  return count;
}

void check_prime_cycle(prime_t *p, bool cyclic[], size_t cur) {
  uint32_t num = prime_nth(p, cur);
  uint32_t max = 1;
  size_t mag = 0;
  while (max <= num) {
    max *= 10;
    mag += 1;
  }
  max /= 10;

  size_t index[mag];
  index[0] = cur;

  // cycle num and check if all cycles are prime
  for (size_t i = 1; i < mag; i++) {
    uint8_t leading = num / max;
    num -= leading * max;
    num *= 10;
    num += leading;

    if(!prime_check(p, num)) {
      return;
    }
    index[i] = prime_which(p, num);
    if (index[i] == SIZE_MAX) {
      return;
    }
  }

  // flag all cyclic primes
  for (size_t i = 0; i < mag; i++) {
    cyclic[index[i]] = true;
  }
}

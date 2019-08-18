#include "solve.h"
#include <stdbool.h>

int32_t solve(int32_t max) {
  int32_t product = 1;
  uint32_t run = 0;
  prime_t p = prime_new();

  // a must be between -max < a < max.
  for (int32_t a = -max + 1; a < max; a++) {
    // b must be prime itself, because f(0)=n^2 + na + b=0^2 + 0n + b = b
    for (int32_t b = 0; prime_nth(&p, b) < max; b++) {
      uint32_t cur = quadratic_prime_run(&p, a, prime_nth(&p, b));

      // if we found a prime run that is long, we keep it and the product
      if (cur > run) {
        run = cur;
        product = a * prime_nth(&p, b);
      }
    }
  }

  return product;
}

uint32_t quadratic_prime_run(prime_t *p, int32_t a, int32_t b) {
  uint32_t n = 0;
  while (true) {
    int32_t cur = n * n + n * a + b;
    // FIXME: performance was better before with prime_index?
    if (cur < 2 || !prime_check(p, cur))
      break;
    n++;
  }

  return n;
}

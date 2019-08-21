#include "solve.h"
#include <euler/math.h>
#include <euler/math.h>
#include <euler/prime.h>

uint32_t solve(uint8_t max) {
  prime_t p = prime_new();

  for (uint8_t n = max; n > 0; n--) {
    for (uint32_t nth = factorial(n); nth != 0; nth--) {
      uint32_t pan = nth_pandigital(n, nth - 1);
      if (prime_check(&p, pan))
        return pan;
    }
  }

  return 0;
}

#include "solve.h"
#include <euler/prime.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

uint64_t solve() {
  prime_t p = prime_new();

  uint64_t num = 1;
  while (true) {
    // next odd number
    num += 2;

    // make sure number is composite
    while (SIZE_MAX != prime_which(&p, num))
      num += 2;

    // use this to keep track if the conjecture holds for num or not
    bool conjecture = false;

    // we start our search at the 2nd prime, because the conjecture only
    // works for odd primes (since twice any square will always be even)
    for (size_t i = 1; prime_nth(&p, i) < num; i++) {
      uint64_t square = num - prime_nth(&p, i);
      square /= 2;
      uint64_t root = sqrt(square);

      if ((root * root) == square) {
        conjecture = true;
        break;
      }
    }

    if (!conjecture)
      return num;
  }
}

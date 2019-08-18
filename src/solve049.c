#include "solve.h"
#include <euler/prime.h>
#include <stddef.h>

uint64_t solve(uint32_t avoid) {
  prime_t p = prime_new();

  // gen all primes up to 10000
  for (size_t i = 0; prime_nth(&p, i) < 10000; i++)
    ;

  // find a possible offset
  for (uint32_t offset = 2; offset < 5000; offset += 2) {
    // find a prime where prime + 2*offset is a 4 digit number
    for (uint32_t i = 1; 2 * offset + prime_nth(&p, i) < 10000; i++) {
      uint32_t first = prime_nth(&p, i);
      uint32_t second = first + offset;
      uint32_t third = second + offset;

      // make sure all the numbers are prime
      if (!prime_check(&p, second))
        continue;
      if (!prime_check(&p, third))
        continue;

      // make sure all are permutations of each other
      if (!permutations(first, second, third))
        continue;

      // if this is not the one we already know about, we got it
      if (first != avoid) {
        return ((first)*10000LL + second) * 10000LL + third;
      }
    }
  }

  return 0;
}

// this function is super inelegant
bool permutations(uint32_t a, uint32_t b, uint32_t c) {
  // extract digits of a
  uint8_t digits_a[4];
  for (size_t i = 0; i < 4; i++) {
    digits_a[i] = a % 10;
    a /= 10;
  }

  // extract digits of b
  uint8_t digits_b[4];
  for (size_t i = 0; i < 4; i++) {
    digits_b[i] = b % 10;
    b /= 10;
  }

  // walk c and mark off digits we've seen
  for (size_t i = 0; i < 4; i++) {
    uint8_t digit = c % 10;
    c /= 10;

    size_t count_a = 0;
    size_t count_b = 0;
    for (size_t i = 0; i < 4; i++) {
      if (!count_a && digits_a[i] && digits_a[i] == digit) {
        digits_a[i] = 0;
        count_a++;
      }
      if (!count_b && digits_b[i] && digits_b[i] == digit) {
        digits_b[i] = 10;
        count_b++;
      }
    }
    if (count_a != 1 || count_b != 1)
      return false;
  }

  return true;
}

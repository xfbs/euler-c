#include "solve.h"
#include <euler/math.h>

// FIXME: use nth_pandigital maybe?
uint64_t solve(uint32_t max) {
  // keeps track of which numbers 0..9 are taken already.
  bool taken[10] = {false};

  // the final result
  uint32_t num = 0;

  // find each digit
  for (uint32_t cur = 10; cur > 0; cur--) {
    num *= 10;

    // which (of the remaining digit) is chosen?
    uint32_t choice = max / factorial(cur - 1);

    max -= choice * factorial(cur - 1);

    // find out which digit was chosen
    uint32_t digit = 0;
    while (choice > 0) {
      if (!taken[digit]) {
        choice--;
      }
      digit++;
    }

    while (taken[digit]) {
      digit++;
    }

    // mark current digit as chosen
    taken[digit] = true;

    num += digit;
  }

  return num;
}

#include "solve.h"
#include <euler/math.h>
#include <math.h>

uint32_t solve(uint32_t digits) {
  uint32_t min = pow(10, digits - 1);
  uint32_t max = pow(10, digits);
  uint32_t match = 0;

  for (uint32_t first = min; first < max; first++) {
    for (uint32_t second = first; second < max; second++) {
      uint32_t product = first * second;
      if (product > match && is_palindrome(product)) {
        match = product;
      }
    }
  }

  return match;
}

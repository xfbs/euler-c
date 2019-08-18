#include "solve.h"
#include <euler/math.h>

uint32_t solve() {
  uint32_t numerator = 1;
  uint32_t denominator = 1;

  for (uint8_t a = 0; a < 10; a++) {
    for (uint8_t b = 0; b < 10; b++) {
      for (uint8_t c = 0; c < 10; c++) {
        for (uint8_t d = 0; d < 10; d++) {
          if (check_fraction(a, b, c, d)) {
            numerator *= 10 * a + b;
            denominator *= 10 * c + d;

            uint64_t frac_gcd = gcd(numerator, denominator);
            numerator /= frac_gcd;
            denominator /= frac_gcd;
          }
        }
      }
    }
  }

  return denominator;
}

bool check_fraction(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
  double frac = (10.0 * a + b) / (10.0 * c + d);
  if (frac > 1.0)
    return false;
  if (frac == 0)
    return false;

  if (b == c && d != 0 && (frac * d) == a)
    return true;
  if (a == d && c != 0 && (frac * c) == b)
    return true;
  return false;
}

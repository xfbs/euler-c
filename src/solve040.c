#include "solve.h"

uint32_t solve() {
  uint32_t solution = champernowne_digit(0) * champernowne_digit(9) *
                      champernowne_digit(99) * champernowne_digit(999) *
                      champernowne_digit(9999) * champernowne_digit(99999) *
                      champernowne_digit(999999);

  return solution;
}

uint8_t champernowne_digit(uint32_t pos) {
  uint32_t mag = 1;
  uint32_t exp = 9;

  while (pos >= (mag * exp)) {
    pos -= mag * exp;
    exp *= 10;
    mag += 1;
  }

  uint32_t num = (exp / 9) + pos / mag;
  uint32_t off = mag - pos % mag - 1;

  for (size_t i = 0; i < off; i++)
    num /= 10;
  return num % 10;
}

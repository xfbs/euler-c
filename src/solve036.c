#include "solve.h"
#include <stdio.h>

uint32_t solve(uint32_t max) {
  uint32_t sum = 0;

  for (uint32_t i = 0; i < max; i++) {
    if (is_palindrome(i, 2) && is_palindrome(i, 10)) {
      sum += i;
    }
  }

  return sum;
}

bool is_palindrome(uint32_t num, uint32_t base) {
  uint32_t mag = 1;
  uint32_t max = base;

  while (num >= max) {
    mag += 1;
    max *= base;
  }

  while (mag > 1) {
    mag -= 2;
    uint32_t right = num % base;
    num /= base;
    max /= base;
    max /= base;
    uint32_t left = num / max;
    if (right != left)
      return false;
    num -= left * max;
  }

  return true;
}

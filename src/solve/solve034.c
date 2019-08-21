#include "solve.h"
#include <euler/math.h>

uint64_t solve(uint64_t max) {
  // pre-populate a list of all the factorials we will need
  uint64_t factorials[10];
  for (uint8_t i = 0; i < 10; i++)
    factorials[i] = factorial(i);

  uint64_t sum = 0;

  for (uint64_t num = 3; num <= max; num++) {
    if (is_curious_number(factorials, num)) {
      sum += num;
    }
  }

  return sum;
}

bool is_curious_number(uint64_t factorials[], uint64_t num) {
  uint64_t cur = num;
  uint64_t sum = 0;

  while (sum < num && cur) {
    sum += factorials[cur % 10];
    cur /= 10;
  }

  return (cur == 0) && (sum == num);
}

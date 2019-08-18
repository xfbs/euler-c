#include "solve.h"

uint32_t solve(uint32_t value) {
  uint32_t coins[] = {200, 100, 50, 20, 10, 5, 2, 1, 0};
  return change(coins, value, 0);
}

uint32_t change(uint32_t coins[], uint32_t value, size_t pos) {
  if (value == 0)
    return 1;
  if (coins[pos + 1] == 0)
    return (value % coins[pos]) == 0 ? 1 : 0;

  uint32_t sum = 0;
  for (uint32_t n = 0; n <= (value / coins[pos]); n++) {
    sum += change(coins, value - n * coins[pos], pos + 1);
  }

  return sum;
}

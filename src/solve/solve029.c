#include "solve.h"
#include <stdbool.h>
#include <string.h>

uint32_t solve(uint32_t max_a, uint32_t max_b) {
  // if all powers were equal, this is what the sum would be
  uint32_t sum = (max_a - 1) * (max_b - 1);

  // basically, the goal here is to find how many powers will be equal to one
  // another, and subtract that from the theoretical count of distinct powers.
  bool b[max_a - 1];
  memset(b, 0, sizeof b);

  for (uint32_t a = 2; a <= max_a; a++) {
    uint32_t product = a * a;
    uint32_t power = 2;
    while (product <= max_a && !b[product - 2]) {
      b[product - 2] = true;

      for (uint32_t b = 2; b <= max_b; b++) {
        uint32_t exponent = b * power;

        for (uint32_t lower = 1; lower < power; lower++) {
          if (((exponent % lower) == 0) && (exponent / lower) <= max_b) {
            sum -= 1;
            break;
          }
        }
      }

      product *= a;
      power += 1;
    }
  }

  return sum;
}

#include "solve.h"
#include <euler/vec16.h>

uint64_t solve(uint32_t exp) {
  vec16_t num = vec16_new(1, 1);

  // compute exp!
  for (uint32_t f = 1; f <= exp; f++) {
    uint16_t carry = 0;
    for (size_t i = 0; i < vec16_len(&num); i++) {
      uint32_t cur = f * (uint32_t)vec16_get(&num, i) + carry;
      vec16_set(&num, i, cur % 10000);
      carry = cur / 10000;
    }

    if (carry != 0) {
      vec16_push(&num, carry);
    }
  }

  // compute sum of digits
  uint64_t sum = 0;
  for (size_t i = 0; i < vec16_len(&num); i++) {
    int pos = 1;
    for (size_t d = 0; d < 4; d++) {
      sum += (vec16_get(&num, i) / pos) % 10;
      pos *= 10;
    }
  }

  return sum;
}

#include "solve.h"
#include "euler/vec8.h"

uint64_t solve(size_t exp) {
  vec8_t num = vec8_new(1, 1);

  // compute 2^exp
  for (size_t i = 0; i < exp; i++) {
    uint8_t carry = 0;
    for (size_t i = 0; i < vec8_len(&num); i++) {
      uint8_t cur = vec8_get(&num, i);
      cur *= 2;
      cur += carry;
      vec8_set(&num, i, cur % 10);
      carry = cur / 10;
    }

    if (carry != 0) {
      vec8_push(&num, carry);
    }
  }

  // compute sum of digits
  uint64_t sum = 0;
  for (size_t i = 0; i < vec8_len(&num); i++) {
    sum += vec8_get(&num, i);
  }

  return sum;
}

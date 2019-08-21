#include "solve.h"
#include <stddef.h>
#include <stdio.h>

uint64_t pandigital(uint32_t d2d3d4, uint32_t d5d6d7, uint32_t d8d9d10) {
  // get whole number
  uint64_t num = 1000000 * d2d3d4 + 1000 * d5d6d7 + d8d9d10;
  uint64_t whole = num;

  // array of digits we've seen
  uint8_t d[10] = {0};

  // mark off digits we've seen
  for (uint8_t i = 0; i < 9; i++) {
    d[num % 10] = 1;
    num /= 10;
  }

  // find the missing digit
  uint8_t count = 0;
  uint8_t digit = 0;
  for (uint8_t i = 0; i < 10; i++) {
    if (d[i] == 0) {
      count++;
      digit = i;
    }
  }

  // if more than one digit is missing, we are bust. otherwise, add it to the
  // final number
  if (count == 1) {
    whole += 1000000000LL * digit;
  } else {
    whole = 0;
  }

  return whole;
}

uint64_t solve() {
  uint64_t sum = 0;

  for (uint32_t d8d9d10 = 0; d8d9d10 < 1000; d8d9d10 += 17) {
    for (uint32_t d7 = 0; d7 < 10; d7++) {
      uint32_t d7d8d9 = 100 * d7 + d8d9d10 / 10;
      if ((d7d8d9 % 13) != 0)
        continue;

      for (uint32_t d6 = 0; d6 < 10; d6++) {
        uint32_t d6d7d8 = 100 * d6 + d7d8d9 / 10;
        if ((d6d7d8 % 11) != 0)
          continue;

        for (uint32_t d5 = 0; d5 < 10; d5++) {
          uint32_t d5d6d7 = 100 * d5 + d6d7d8 / 10;
          if ((d5d6d7 % 7) != 0)
            continue;

          for (uint32_t d4 = 0; d4 < 10; d4++) {
            uint32_t d4d5d6 = 100 * d4 + d5d6d7 / 10;
            if ((d4d5d6 % 5) != 0)
              continue;

            for (uint32_t d3 = 0; d3 < 10; d3++) {
              uint32_t d3d4d5 = 100 * d3 + d4d5d6 / 10;
              if ((d3d4d5 % 3) != 0)
                continue;

              for (uint32_t d2 = 0; d2 < 10; d2++) {
                uint32_t d2d3d4 = 100 * d2 + d3d4d5 / 10;
                if ((d2d3d4 % 2) != 0)
                  continue;
                sum += pandigital(d2d3d4, d5d6d7, d8d9d10);
              }
            }
          }
        }
      }
    }
  }

  return sum;
}

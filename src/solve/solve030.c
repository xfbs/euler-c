#include "solve.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

uint32_t solve() {
  // TODO: can we simplify this?
  uint8_t nums[6] = {2, 0, 0, 0, 0, 0};
  uint32_t sum = 0;

  while (true) {
    uint32_t c = digit_power_sum(nums);
    sum += c;

    bool wrong = true;
    while (wrong) {
      nums[5]++;
      for (size_t i = 5; i >= 1 && nums[i] == 10; i--) {
        nums[i - 1]++;
        nums[i] = 0;
      }
      if (nums[0] == 10)
        break;
      wrong = false;
      for (size_t i = 0; i < 5; i++) {
        if (nums[i] < nums[i + 1])
          wrong = true;
      }
    }

    if (nums[0] == 10)
      break;
  }

  return sum;
}

uint32_t digit_power_sum(uint8_t nums[6]) {
  uint8_t copy[6];
  memcpy(copy, nums, 6 * sizeof(uint8_t));

  uint32_t sum = 0;
  for (size_t i = 0; i < 6; i++) {
    uint32_t num = nums[i];
    sum += num * num * num * num * num;
  }

  uint32_t saved = sum;
  for (size_t p = 0; p < 6; p++) {
    uint8_t num = sum % 10;

    for (size_t i = 0; i < 6; i++) {
      if (copy[i] == num) {
        copy[i] = 0;
        sum /= 10;
        break;
      }
    }
  }

  for (size_t i = 0; i < 6; i++) {
    if (copy[i] != 0)
      return 0;
  }

  if (sum == 0) {
    return saved;
  } else {
    return 0;
  }
}

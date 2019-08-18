#include "solve.h"
#include <euler/vec.h>

uint64_t get(vecp_t *grid, int64_t x, int64_t y) {
  if (0 <= x && x < vec_len(grid)) {
    vec8_t *row = vec_get(grid, x);

    if (0 <= y && y < vec_len(row)) {
      return vec_get(row, y);
    }
  }

  return 0;
}

uint64_t max_product(vecp_t *grid, int8_t dir_x, int8_t dir_y, size_t len) {
  uint64_t max = 0;
  for (size_t x = 0; x < vec_len(grid); x++) {
    vec8_t *row = vec_get(grid, x);
    for (size_t y = 0; y < vec_len(row); y++) {
      uint64_t cur = 1;
      for (int64_t c = 0; c < len; c++) {
        cur *= get(grid, c * dir_x + x, c * dir_y + y);
      }
      if (cur > max)
        max = cur;
    }
  }

  return max;
}

uint64_t solve(vecp_t *grid, size_t len) {
  uint64_t max = 0;
  int8_t dirs[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};

  for (size_t i = 0; i < 4; i++) {
    uint64_t cur = max_product(grid, dirs[i][0], dirs[i][1], len);
    if (cur > max)
      max = cur;
  }

  return max;
}

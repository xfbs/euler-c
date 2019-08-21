#include "solve.h"

uint32_t solve(triangle_t *t) {
  while (t->rows != 1) {
    triangle_simplify(t);
  }

  return triangle_get(*t, 0, 0);
}

uint32_t triangle_get(triangle_t t, size_t row, size_t index) {
  size_t offset = row * (row + 1) / 2;
  return t.data[offset + index];
}

uint32_t triangle_set(triangle_t t, size_t row, size_t index, uint32_t num) {
  size_t offset = row * (row + 1) / 2;
  t.data[offset + index] = num;
  return num;
}

void triangle_simplify(triangle_t *t) {
  if (t->rows < 2)
    return;
  size_t row = t->rows - 2;

  for (size_t index = 0; index <= row; index++) {
    uint32_t cur = triangle_get(*t, row, index);
    uint32_t left = triangle_get(*t, row + 1, index);
    uint32_t right = triangle_get(*t, row + 1, index + 1);

    if (left > right) {
      triangle_set(*t, row, index, cur + left);
    } else {
      triangle_set(*t, row, index, cur + right);
    }
  }

  t->rows--;
}

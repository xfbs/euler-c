#include "solve.h"

uint32_t solve(uint32_t num) {
  uint32_t sum = 0;

  for (uint32_t i = 1; i <= num; i++) {
    sum += number_letter_count(i);
  }

  return sum;
}

static uint32_t teens_letter_count(uint32_t num) {
  uint8_t counts[27][2] = {
      {1, 3},  /* one */
      {2, 3},  /* two */
      {3, 5},  /* three */
      {4, 4},  /* four */
      {5, 4},  /* five */
      {6, 3},  /* six */
      {7, 5},  /* seven */
      {8, 5},  /* eight */
      {9, 4},  /* nine */
      {10, 3}, /* ten */
      {11, 6}, /* eleven */
      {12, 6}, /* twelve */
      {13, 8}, /* thirteen */
      {14, 8}, /* fourteen */
      {15, 7}, /* fifteen */
      {16, 7}, /* sixteen */
      {17, 9}, /* seventeen */
      {18, 8}, /* eighteen */
      {19, 8}, /* nineteen */
      {20, 6}, /* twenty */
      {30, 6}, /* thirty */
      {40, 5}, /* forty */
      {50, 5}, /* fifty */
      {60, 5}, /* sixty */
      {70, 7}, /* seventy */
      {80, 6}, /* eighty */
      {90, 6}  /* ninety */
  };

  uint32_t count = 0;
  for (int i = 26; i >= 0; i--) {
    if (num >= counts[i][0]) {
      count += counts[i][1];
      num -= counts[i][0];
    }
  }

  return count;
}

static uint32_t hundreds_letter_count(uint32_t num) {
  uint8_t hundreds = num / 100;
  uint32_t count = 0;

  if (hundreds > 0) {
    count += teens_letter_count(hundreds);
    count += 7; /* hundred */
  }

  if (num % 100) {
    count += teens_letter_count(num % 100);
  }

  if (hundreds && (num % 100)) {
    count += 3; /* and */
  }

  return count;
}

static uint32_t thousands_letter_count(uint32_t num) {
  uint32_t thousands = num / 1000;
  uint32_t count = 0;

  if (thousands > 0) {
    count += hundreds_letter_count(thousands);
    count += 8; /* thousand */
  }

  if (num % 1000) {
    count += hundreds_letter_count(num % 1000);
  }

  return count;
}

uint32_t number_letter_count(uint32_t num) {
  return thousands_letter_count(num);
}

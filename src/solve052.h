#include <euler/common.h>
#pragma once

// TODO: candidate for euler?
typedef struct {
    // how many digits are there in this number? eg. 0 if the number is 0, 1 if
    // the number is 1..9, 2 if the the number is 10..99
    uint8_t count;

    // the digits of the number, in reverse order (lowest magnitude first)
    uint8_t digits[20];
} digits_t;

// find a number x such that 2x, 3x, 4x, 5x, and 6x contain the same digits.
uint64_t solve();

// for a given number x, check if 2x, 3x, 4x, 5x and 6x contain the same digits
bool is_permuted_multiple(uint64_t x);

// take a number and compute its digits in the form of a digits_t struct.
digits_t num_to_digits(uint64_t n);

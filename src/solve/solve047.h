#include <euler/prime.h>
#include <euler/common.h>
#pragma once

// finds the first number of the first `cnt` consecutive integers to have `cnt`
// distinct prime factors each.
uint64_t solve(uint8_t cnt);

// checks if a given number is the first number is a sequence that is `count`
// long where each number has `count` prime factors that are distinct.
bool distinct_prime_factors(prime_t *p, uint8_t count, uint64_t num);

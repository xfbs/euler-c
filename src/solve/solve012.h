#pragma once
#include "euler.h"
#include <euler/prime.h>

uint32_t highly_divisible_triangular(size_t max);
uint32_t factor_count(prime_t *p, uint32_t);

struct euler_result solve012(json_t *input);
extern const struct euler_input input012[];

#pragma once
#include "euler.h"

uint32_t sum_multiples(uint32_t max, uint32_t a, uint32_t b);
uint32_t sum_divisible(uint32_t max, uint32_t divisor);

struct euler_result solve001(const struct euler_input *input);
extern const struct euler_input input001[];

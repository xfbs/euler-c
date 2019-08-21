#include <euler/common.h>
#include <euler/vecp.h>
#pragma once

uint64_t get(vecp_t *grid, int64_t x, int64_t y);
uint64_t solve(vecp_t *v, size_t len);
uint64_t max_product(vecp_t *grid, int8_t dir_x, int8_t dir_y, size_t len);

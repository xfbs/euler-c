#include <euler/common.h>
#include <euler/vecp.h>
#pragma once

// TODO: export weight function to euler
uint64_t solve(vecp_t *v);
uint64_t weight(const char *str);
bool is_triangle_word(const char *word);
bool is_triangle_number(uint64_t num);

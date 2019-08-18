#include <euler/common.h>
#pragma once

// TODO: rewrite with vecp/vec64
typedef struct {
    uint64_t **cache;
    size_t x;
    size_t y;
} cache_t;

uint64_t solve(size_t x, size_t y);
uint64_t paths(cache_t cache, size_t x, size_t y);

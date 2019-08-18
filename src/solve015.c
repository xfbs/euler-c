#include "solve.h"
#include <stdlib.h>

uint64_t solve(size_t x, size_t y) {
  // allocate new cache object, using calloc so the memory comes pre-zeroed.
  // we allocate a two-dimensional array that is x+1 by y+1
  cache_t cache;
  cache.x = x + 1;
  cache.y = y + 1;
  cache.cache = calloc(cache.x, sizeof(uint64_t *));
  for (size_t i = 0; i < cache.x; i++) {
    cache.cache[i] = calloc(cache.y, sizeof(uint64_t *));
  }

  // calculate the paths to position [x, y]
  uint64_t p = paths(cache, x, y);

  // memory cleanup and return
  for (size_t i = 0; i < cache.x; i++) {
    free(cache.cache[i]);
  }
  free(cache.cache);

  return p;
}

uint64_t paths(cache_t c, size_t x, size_t y) {
  // known shortcuts
  if (x == 0 || y == 0)
    return 1;
  if (x == 1)
    return y + 1;
  if (y == 1)
    return x + 1;
  if (x == 2)
    return (y + 1) * (y + 2) / 2;
  if (y == 2)
    return (x + 1) * (x + 2) / 2;

  // look up result in cache, since it's symmetrical we can look up both
  // [x, y] and [y, x].
  if (x < c.x && y < c.y) {
    if (c.cache[x][y] != 0) {
      return c.cache[x][y];
    }
  }
  if (y < c.x && x < c.y) {
    if (c.cache[y][x] != 0) {
      return c.cache[y][x];
    }
  }

  // if we don't have a result, we need to compute one — this means
  // using recursion.
  uint64_t result = paths(c, x, y - 1) + paths(c, x - 1, y);

  // since we got a result for the first time, we need to store it in the
  // cache.
  if (x < c.x && y < c.y)
    c.cache[x][y] = result;
  if (y < c.x && x < c.y)
    c.cache[y][x] = result;

  return result;
}

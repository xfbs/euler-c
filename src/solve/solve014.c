#include "solve.h"
#include <euler/collatz.h>

uint32_t solve(uint32_t limit) {
  // the collatz cache basically memoizes the collatz function for efficiency
  collatz_cache_t cache = collatz_cache(limit);

  for (uint32_t num = 2; num < limit; num++) {
    // calculate the collatz sequence length
    collatz_length(num, cache);
  }

  uint32_t longest = collatz_longest(cache);
  collatz_free(&cache);
  return longest;
}

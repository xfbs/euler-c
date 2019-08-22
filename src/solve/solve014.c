#include "solve014.h"
#include <euler/collatz.h>

uint32_t longest_collatz_sequence(uint32_t limit) {
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

struct euler_result solve014(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input014, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", longest_collatz_sequence(max));

  return result;
}

const struct euler_input input014[] = {
  euler_input_number(max, "maximum collatz starting point", 1000000, 0, INT64_MAX),
  {NULL},
};

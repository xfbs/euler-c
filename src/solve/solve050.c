#include "solve050.h"
#include <euler/prime.h>
#include <stddef.h>

uint64_t consecutive_prime_sum(uint64_t max) {
  prime_t p = prime_new();

  // find the max len
  size_t max_len;
  uint64_t sum_pre = 0;
  for (max_len = 0; sum_pre + prime_nth(&p, max_len) < max; max_len++) {
    sum_pre += prime_nth(&p, max_len);
  }

  // sum of primes[0] ... primes[len-1]
  for (size_t len = max_len; len > 1; len--) {
    // running sum of primes[i-len] ... primes[i]
    uint64_t sum = sum_pre;

    // subtract last prime for next iteration
    sum_pre -= prime_nth(&p, len - 1);

    for (size_t i = len; sum < max; i++) {
      if (prime_check(&p, sum)) {
        prime_free(&p);
        return sum;
      }

      sum -= prime_nth(&p, i - len);
      sum += prime_nth(&p, i);
    }
  }

  prime_free(&p);
  return 0;
}

struct euler_result solve050(json_t *input) {
  struct euler_result result;
  int64_t max;

  result = euler_input_get(input050, input, &max);
  if(!result.ok) {
    return result;
  }

  euler_write(&result, "%llu", consecutive_prime_sum(max));

  return result;
}

const struct euler_input input050[] = {
  euler_input_number(max, "maximum prime.", 1000000, 0, INT64_MAX),
  {NULL},
};

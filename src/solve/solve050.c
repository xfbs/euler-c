#include "solve.h"
#include <euler/prime.h>
#include <stddef.h>

uint64_t solve(uint64_t max) {
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

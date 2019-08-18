#include "solve.h"

static const size_t factors_size = 10240;

void make_factors(prime_t *p, size_t off, uint8_t f[], uint8_t ct);

uint64_t solve(uint8_t count) {
  // factors is a `window` of numbers from `window_offset` to
  // `window_offset + window_size`. it keeps a list of how many prime factors
  // each number has (up to `count + 1`, anything above we don't care about).
  uint8_t factors[factors_size];
  prime_t primes = prime_new();

  for (size_t factors_offset = 0;; factors_offset += factors_size - count) {
    size_t factors_max = factors_offset + factors_size;
    make_factors(&primes, factors_offset, factors, count);

    // check which `count` consecutive numbers have `count` distinct prime
    // factors
    for (size_t num = factors_offset; num < (factors_max - count); num++) {
      size_t offset;
      for (offset = 0; offset < count; offset++) {
        if (factors[num + offset - factors_offset] != count)
          break;
      }

      if (offset == count) {
        if (distinct_prime_factors(&primes, count, num)) {
          prime_free(&primes);
          return num;
        }
      } else {
        // we can safely skip `offset` numbers
        num += offset;
      }
    }
  }
}

void make_factors(prime_t *primes, size_t offset, uint8_t factors[],
                  uint8_t count) {
  size_t max = offset + factors_size;

  // reset window to all-zeroes.
  for (size_t pos = 0; pos < factors_size; pos++)
    factors[pos] = 0;

  // iterate through the prime numbers, and for every number in the
  // `prime_factors` window, set how many prime factors it has
  for (size_t i = 0; prime_nth(primes, i) < max; i++) {
    uint64_t prime = prime_nth(primes, i);
    uint64_t cur = prime;

    while (cur < offset)
      cur += prime;
    while (cur < max) {
      // if the prime factors are already bigger than count, we
      // ignore - we don't want overflow errors and we only care if
      // the prime factors are equal to count or not anyways.
      if (factors[cur - offset] <= count) {
        factors[cur - offset]++;
      }

      cur += prime;
    }
  }
}

bool distinct_prime_factors(prime_t *p, uint8_t count, uint64_t num) {
  for (uint64_t cur = num; cur < (num + count); cur++) {
    uint8_t factors = 0;
    uint64_t state = cur;
    for (size_t i = 0; factors < count; i++) {
      // oops, current number has less than `count` prime factors
      if (state == 1)
        return false;

      // current prime candidate
      uint64_t prime = prime_nth(p, i);

      if ((cur % prime) == 0) {
        uint64_t factor = prime;
        while ((cur % (factor * prime)) == 0)
          factor *= prime;
        state /= factor;
        factors += 1;

        // make sure no other numbers have this prime as a factor
        for (uint64_t other = num; other < (num + count); other++) {
          if (cur != other) {
            if (other % factor == 0 && other % (factor * prime) != 0) {
              // another number has the same factor
              return false;
            }
          }
        }
      }
    }

    // oops, more than `count` prime factors
    if (state != 1)
      return false;
  }

  return true;
}

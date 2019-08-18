#include "solve.h"
#include <euler/prime.h>

uint64_t solve(uint32_t pos) {
  prime_t p = prime_new();

  // generate nth prime (subtract pos by one because prime_nth is
  // zero-indexed)
  uint64_t prime = prime_nth(&p, pos - 1);

  prime_free(&p);

  return prime;
}

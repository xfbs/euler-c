#include "solve.h"
#include <stdbool.h>

uint64_t triangular(uint32_t t) { return (1LL + t) * t / 2; }

uint64_t pentagonal(uint32_t p) { return (3LL * p - 1) * p / 2; }

uint64_t hexagonal(uint32_t h) { return (2LL * h - 1) * h; }

uint64_t solve(uint32_t t, uint32_t p, uint32_t h) {
  uint64_t tt = triangular(t);
  uint64_t pp = pentagonal(p);
  uint64_t hh = hexagonal(h);

  while (true) {
    bool is_triangular = false;
    bool is_pentagonal = false;

    h += 1;
    hh = hexagonal(h);

    while (tt <= hh) {
      t += 1;
      tt = triangular(t);
      if (tt == hh)
        is_triangular = true;
    }

    while (pp <= hh) {
      p += 1;
      pp = pentagonal(p);
      if (pp == hh)
        is_pentagonal = true;
    }

    if (is_pentagonal && is_triangular) {
      return hh;
    }
  }
}

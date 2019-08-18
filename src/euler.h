#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

struct euler_result {
  bool ok;
  char result[256];
  size_t length;
};

typedef struct euler_result euler_function(void);

struct euler_problem {
  size_t number;
  const char *name;
  const char *solution;
  euler_function *function;
};

extern struct euler_problem euler_problems[];

void euler_write(struct euler_result *result, const char *format, ...);
bool euler_check(const struct euler_problem *problem, const struct euler_result *result);

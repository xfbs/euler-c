#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define euler_input_number(_name, _desc, _def) \
  {.name = #_name, .desc = _desc, .type = EULER_NUMBER, .data._number = _def}

struct euler_result {
  bool ok;
  char result[256];
  size_t length;
  double time;
};

enum euler_type {
  EULER_NUMBER,
  EULER_FLOAT,
  EULER_STRING,
};

struct euler_input {
  const char *name;
  const char *desc;
  enum euler_type type;
  union {
    int64_t _number;
    double _double;
    const char *_string;
  } data;
};

typedef struct euler_result euler_function(const struct euler_input *input);

struct euler_problem {
  size_t number;
  const char *name;
  const char *hash;
  const unsigned char *desc;
  euler_function *solve;
  const struct euler_input *input;
};

extern const struct euler_problem *euler_problems[];

void euler_write(struct euler_result *result, const char *format, ...);
bool euler_check(const struct euler_problem *problem, const struct euler_result *result);
struct euler_result euler_solve(const struct euler_problem *problem);
const char *euler_type_str(enum euler_type type);

int64_t euler_input_get_number(const struct euler_input *input, const char *name, struct euler_result *result);

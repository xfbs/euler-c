#include "euler.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <bcrypt.h>
#include <time.h>

void euler_write(struct euler_result *result, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int ret = vsnprintf(result->result, sizeof(result->result), format, args);

  if(ret < 0) {
    result->ok = false;
  } else {
    result->ok = true;
    result->length = ret;
  }

  va_end(args);
}

bool euler_check(const struct euler_problem *problem, const struct euler_result *result) {
  return 0 == bcrypt_checkpass(result->result, problem->hash);
}

struct euler_result euler_solve(const struct euler_problem *problem) {
  struct euler_result result;

  if(problem->solve) {
    clock_t before = clock();
    result = problem->solve(problem->input);
    clock_t total = clock() - before;
    result.time = total / (double)CLOCKS_PER_SEC;
  } else {
    result.ok = false;
    result.time = 0;

    // we assume result is large enough to hold this.
    strcpy(result.result, "No solution implemented.");
  }

  return result;
}

const char *euler_type_str(enum euler_type type) {
  switch(type) {
    case EULER_NUMBER:
      return "NUMBER";
    case EULER_FLOAT:
      return "FLOAT";
    case EULER_STRING:
      return "STRING";
    default:
      return NULL;
  }
}

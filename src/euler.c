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

int64_t euler_input_get_number(
    const struct euler_input *input,
    const char *name,
    struct euler_result *result) {
  for(size_t i = 0; input[i].name; i++) {
    if(0 == strcmp(name, input[i].name)) {
      if(input[i].type != EULER_NUMBER) {
        euler_write(result, "Wrong type for input %x: expected NUMBER, got %x.", name, euler_type_str(input[i].type));
        result->ok = false;
        return 0;
      }

      result->ok = true;
      return input[i].data._number;
    }
  }

  euler_write(result, "Can't find input %s.", name);
  result->ok = false;
  return 0;
}

const struct euler_problem *euler_problem_get(size_t num) {
  for(size_t i = 0; euler_problems[i]; i++) {
    if(euler_problems[i]->number == num) {
      return euler_problems[i];
    }
  }

  return NULL;
}

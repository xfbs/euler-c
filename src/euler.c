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

struct euler_result euler_solve(const struct euler_problem *problem, json_t *values) {
  struct euler_result result;

  if(problem->solve) {
    clock_t before = clock();
    result = problem->solve(values);
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

struct euler_result euler_input_get(const struct euler_input *input, json_t *values, ...) {
  va_list args;
  va_start(args, values);
  struct euler_result result = {.ok = true};

  for(size_t i = 0; input[i].name; i++) {
    json_t *value = NULL;

    if(values) {
      value = json_object_get(values, input[i].name);
    }

    int64_t *number;
    double *decimal;
    const char **string;

    switch(input[i].type) {
      case EULER_NUMBER:
        // get the next pointer
        number = va_arg(args, int64_t *);

        // parse from input
        if(value && json_is_integer(value)) {
          *number = json_integer_value(value);

          if(*number < input[i].limits.n.min) {
            euler_write(&result, "Error parsing arg: %lli is smaller than minimum %lli.", *number, input[i].limits.n.min);
            result.ok = false;
            json_decref(value);
            goto exit;
          }

          if(*number > input[i].limits.n.max) {
            euler_write(&result, "Error parsing arg: %lli is bigger than maximum %lli.", *number, input[i].limits.n.max);
            result.ok = false;
            json_decref(value);
          }
        } else {
          // use default
          *number = input[i].data._number;
        }
        break;
      case EULER_FLOAT:
        decimal = va_arg(args, double *);
        break;
      case EULER_STRING:
        string = va_arg(args, const char **);
        break;
    }

    json_decref(value);
  }

exit:
  va_end(args);

  return result;
}

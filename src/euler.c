#include "euler.h"
#include <stdarg.h>
#include <stdio.h>

void euler_write(struct euler_result *result, const char *format, ...) {
  va_list args;
  va_start(args, format);

  int ret = vsnprintf(result->result, sizeof(result->result), format, args);

  if(ret < 0) {
    result->ok = false;
  } else {
    result->length = ret;
  }

  va_end(args);
}

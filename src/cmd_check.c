#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

int check(int argc, char *argv[]) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];
    struct euler_result result = euler_solve(problem);
    bool correct = false;

    // only check if there was no error.
    if(result.ok) {
      correct = euler_check(problem, &result);
    }

    printf("%s result: %s (%s)\n", problem->name, result.result, correct ? "ok" : "err");
  }

  return 0;
}


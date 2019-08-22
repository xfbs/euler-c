#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

int check(int argc, char *argv[]) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->solve) {
      struct euler_result result = euler_solve(problem, NULL);
      bool correct = false;

      // only check if there was no error.
      if(result.ok) {
        correct = euler_check(problem, &result);
        printf(
            "%03zu %s (\033[0;34m%.2fms\033[0m)\n",
            problem->number,
            correct ? "\033[0;32mcorrect\033[0m" : "\033[0;31mwrong\033[0m",
            result.time / 1000);
      } else {
        printf("%03zu \033[0;31merror\033[0m: %s\n", problem->number, result.result);
      }

    }
  }

  return 0;
}


#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

int run(int argc, char *argv[]) {
  size_t num = 1;
  const struct euler_problem *problem = NULL;

  for(size_t i = 0; euler_problems[i]; i++) {
    if(euler_problems[i]->number == num) {
      problem = euler_problems[i];
    }
  }

  if(problem) {
    struct euler_result result = euler_solve(problem, NULL);
    bool correct = euler_check(problem, &result);

    printf("%s result: %s (%s)\n", problem->name, result.result, correct ? "ok" : "err");
  } else {
    printf("problem not found.\n");
  }

  return 0;
}

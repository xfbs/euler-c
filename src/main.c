#include "euler.h"
#include <stdio.h>

int main() {

  for(size_t i = 0; euler_problems[i].number; i++) {
    struct euler_problem *problem = &euler_problems[i];
    struct euler_result result = problem->function();

    printf("%s result: %s\n", problem->name, result.result);
  }

  return 0;
}

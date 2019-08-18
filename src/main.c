#include "euler.h"
#include <stdio.h>
#include <string.h>

typedef int subcommand_func(int argc, char *argv[]);

struct subcommand {
  const char *name;
  subcommand_func *func;
  const char *desc;
};

struct subcommand subcommands[];

int main(int argc, char *argv[]) {
  // default thing to run
  if(argc < 2) {
    return subcommands[0].func(argc, argv);
  }

  // find subcommand
  for(size_t i = 0; subcommands[i].name; i++) {
    if(0 == strcmp(subcommands[i].name, argv[1])) {
      return subcommands[i].func(argc, argv);
    }
  }

  // fallback
  return subcommands[0].func(argc, argv);
}

int help(int argc, char *argv[]) {
  fprintf(
      stderr,
      "Usage: %s [SUBCOMMAND] [OPTIONS]\n\n"
      "SUBCOMMAND\n",
      argv[0]);

  for(size_t i = 0; subcommands[i].name; i++) {
    fprintf(
        stderr,
        "%10s  %s\n",
        subcommands[i].name,
        subcommands[i].desc);
  }

  return 0;
}

int check(int argc, char *argv[]) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];
    struct euler_result result = euler_solve(problem);
    bool correct = euler_check(problem, &result);

    printf("%s result: %s (%s)\n", problem->name, result.result, correct ? "ok" : "err");
  }

  return 0;
}

int list(int argc, char *argv[]) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    printf("%03zu %s\n", problem->number, problem->name);
  }

  return 0;
}

int run(int argc, char *argv[]) {
  size_t num = 1;
  const struct euler_problem *problem = NULL;

  for(size_t i = 0; euler_problems[i]; i++) {
    if(euler_problems[i]->number == num) {
      problem = euler_problems[i];
    }
  }

  if(problem) {
    struct euler_result result = euler_solve(problem);
    bool correct = euler_check(problem, &result);

    printf("%s result: %s (%s)\n", problem->name, result.result, correct ? "ok" : "err");
  } else {
    printf("problem not found.\n");
  }

  return 0;
}

struct subcommand subcommands[] = {
  {"help", help, "Show this help text."},
  {"check", check, "Check that the solutions are correct."},
  {"list", list, "List all known problems."},
  {"run", run, "Run a specified problem."},
  {NULL, NULL},
};

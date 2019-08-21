#include "cmd.h"
#include <stddef.h>

struct subcommand subcommands[] = {
  {"help", help, "Show this help text."},
  {"check", check, "Check that the solutions are correct."},
  {"list", list, "List all known problems."},
  {"view", view, "View a specific problem."},
  {"run", run, "Run a specified problem."},
  {NULL, NULL},
};

#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

int help(int argc, char *argv[]) {
  fprintf(
      stderr,
      "Project Euler solutions by @xfbs.\n"
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

  fprintf(
      stderr,
      "\n"
      "To get help on a subcommand, execute it with the -h flag. For example, try\n\n"
      "    %s check -h\n\n"
      "For more information, check out https://projecteuler.net/.\n",
      argv[0]);

  return 0;
}


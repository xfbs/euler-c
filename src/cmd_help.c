#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

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


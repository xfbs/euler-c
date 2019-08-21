#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>

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


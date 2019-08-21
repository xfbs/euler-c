#pragma once

typedef int subcommand_func(int argc, char *argv[]);

struct subcommand {
  const char *name;
  subcommand_func *func;
  const char *desc;
};

extern struct subcommand subcommands[];

int help(int argc, char *argv[]);
int check(int argc, char *argv[]);
int list(int argc, char *argv[]);
int run(int argc, char *argv[]);
int info(int argc, char *argv[]);
int view(int argc, char *argv[]);

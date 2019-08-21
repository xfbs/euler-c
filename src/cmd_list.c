#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <jansson.h>

struct list_opts {
  bool help;
  bool solved;
  bool unsolved;
  bool json;
  size_t amount;
};

int list_help(const char *prog);
int list_normal(struct list_opts opts);
int list_json(struct list_opts opts);

int list(int argc, char *argv[]) {
  const char *short_opts = "hsan:uj";
  static struct option long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"all", no_argument, NULL, 'a'},
    {"unsolved", no_argument, NULL, 'u'},
    {"solved", no_argument, NULL, 's'},
    {"json", no_argument, NULL, 'j'},
    {"amount", required_argument, NULL, 'n'},
    {NULL, no_argument, NULL, 0}
  };

  struct list_opts opts = {false, .solved = true};

  while(true) {
    int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

    if(opt < 0) break;

    switch(opt) {
      case 0: break;
      case 'h': opts.help = true; break;
      case 'a':
        opts.unsolved = true;
        opts.solved = true;
        break;
      case 's':
        opts.solved = true;
        opts.unsolved = false;
        break;
      case 'u':
        opts.solved = false;
        opts.unsolved = true;
        break;
      case 'n':
        opts.amount = atoi(optarg);
        break;
      case 'j': opts.json = true; break;
      case '?':
      default:
        fprintf(stderr, "Error unrecognised: %s\n", argv[optind]);
        opts.help = true;
        break;
    }
  }

  if(opts.help) {
    return list_help(argv[0]);
  }

  if(opts.json) {
    return list_json(opts);
  } else {
    return list_normal(opts);
  }
}

int list_help(const char *progname) {
  fprintf(
      stderr,
      "List known problems."
      "Usage: %s help [OPTIONS]\n\n"
      "OPTIONS\n"
      "  -h, --help        Show this help text.\n"
      "  -s, --solved      Show only solved (default).\n"
      "  -u, --unsolved    Show only unsolved.\n"
      "  -a, --all         Show both solved and unsolved.\n"
      "  -n, --amount <n>  Show only the first n problems.\n"
      "  -j, --json        Output as JSON.\n",
      progname);

  return 0;
}

int list_normal(struct list_opts opts) {
  size_t amount = 0;
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if((opts.solved && problem->solve) || (opts.unsolved && !problem->solve)) {
      printf("%03zu %s\n", problem->number, problem->name);

      amount++;
      if(opts.amount && opts.amount == amount) break;
    }
  }

  return 0;
}

int list_json(struct list_opts opts) {
  json_t *list = json_array();
  size_t amount = 0;

  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if((opts.solved && problem->solve) || (opts.unsolved && !problem->solve)) {
      json_t *obj = json_object();
      json_object_set_new(obj, "name", json_string(problem->name));
      json_object_set_new(obj, "hash", json_string(problem->hash));
      json_object_set_new(obj, "number", json_integer(problem->number));

      json_array_append_new(list, obj);

      amount++;
      if(opts.amount && opts.amount == amount) break;
    }
  }

  char *out = json_dumps(list, JSON_COMPACT);
  printf("%s\n", out);
  free(out);
  json_decref(list);

  return 0;
}

#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <jansson.h>

struct list_opts {
  bool help;
  bool all;
  bool json;
};

int list_help(const char *prog);
int list_normal(struct list_opts opts);
int list_json(struct list_opts opts);

int list(int argc, char *argv[]) {
  const char *short_opts = "haj";
  static struct option long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"all", no_argument, NULL, 'a'},
    {"json", no_argument, NULL, 'j'},
    {NULL, no_argument, NULL, 0}
  };

  struct list_opts opts = {false};

  while(true) {
    int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

    if(opt < 0) break;

    switch(opt) {
      case 0: break;
      case 'h': opts.help = true; break;
      case 'a': opts.all = true; break;
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
      "Usage: %s help [OPTIONS]\n\n"
      "OPTIONS\n"
      "  -h, --help   Show this help text.\n"
      "  -a, --all    Show all (also unsolved).\n"
      "  -j, --json   Output as JSON.\n",
      progname);

  return 0;
}

int list_normal(struct list_opts opts) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->solve || opts.all) {
      printf("%03zu %s\n", problem->number, problem->name);
    }
  }

  return 0;
}

int list_json(struct list_opts opts) {
  json_t *list = json_array();

  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->solve || opts.all) {
      json_t *obj = json_object();
      json_object_set_new(obj, "name", json_string(problem->name));
      json_object_set_new(obj, "hash", json_string(problem->hash));
      json_object_set_new(obj, "number", json_integer(problem->number));

      json_array_append_new(list, obj);
    }
  }

  char *out = json_dumps(list, JSON_COMPACT);
  printf("%s\n", out);
  free(out);
  json_decref(list);

  return 0;
}

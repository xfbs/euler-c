#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <jansson.h>

struct view_opts {
  bool help;
  bool json;
  size_t number;
};

int view_help(const char *prog);
int view_normal(struct view_opts opts);
int view_json(struct view_opts opts);

int view(int argc, char *argv[]) {
  const char *short_opts = "haj";
  static struct option long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"json", no_argument, NULL, 'j'},
    {NULL, no_argument, NULL, 0}
  };

  struct view_opts opts = {false};

  while(true) {
    int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

    if(opt < 0) break;

    switch(opt) {
      case 0: break;
      case 'h': opts.help = true; break;
      case 'j': opts.json = true; break;
      case '?':
      default:
        fprintf(stderr, "Error unrecognised: %s\n", argv[optind]);
        opts.help = true;
        break;
    }
  }

  if((optind + 2) != argc) {
    opts.help = true;
  }

  if(opts.help) {
    return view_help(argv[0]);
  }

  // parse requested number.
  opts.number = atoi(argv[optind + 1]);

  if(opts.json) {
    return view_json(opts);
  } else {
    return view_normal(opts);
  }
}

int view_help(const char *progname) {
  fprintf(
      stderr,
      "Usage: %s help [OPTIONS] number\n\n"
      "OPTIONS\n"
      "  -h, --help   Show this help text.\n"
      "  -j, --json   Output as JSON.\n",
      progname);

  return 0;
}

int view_normal(struct view_opts opts) {
  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->number == opts.number) {
      printf("Problem  %03zu\n", problem->number);
      printf("Title    %s\n", problem->name);
      printf("Hash     %s\n", problem->hash);
      printf("Solve    %s\n", problem->solve ? "Yes" : "No");

      if(problem->input) {
        printf("\n");
        printf("Inputs\n");

        for(size_t i = 0; problem->input[i].name; i++) {
          const struct euler_input *input = &problem->input[i];
          switch(problem->input[i].type) {
            case EULER_NUMBER:
              printf("number %s (%llu) %s\n", input->name, input->data._number, input->desc);
              break;
            case EULER_FLOAT:
              printf("float %s (%lf) %s\n", input->name, input->data._double, input->desc);
              break;
            case EULER_STRING:
              printf("string %s ('%s') %s\n", input->name, input->data._string, input->desc);
              break;
          }
        }
      }
    }
  }

  return 0;
}

int view_json(struct view_opts opts) {
  json_t *obj = json_object();

  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->number == opts.number) {
      json_object_set_new(obj, "name", json_string(problem->name));
      json_object_set_new(obj, "hash", json_string(problem->hash));
      json_object_set_new(obj, "number", json_integer(problem->number));
    }
  }

  char *out = json_dumps(obj, JSON_COMPACT);
  printf("%s\n", out);
  free(out);
  json_decref(obj);

  return 0;
}

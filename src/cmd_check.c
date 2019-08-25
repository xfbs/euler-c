#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <jansson.h>

struct check_opts {
  bool help;
  bool json;
  size_t threads;
  uint32_t timeout;
};

int check_help(const char *progname);
int check_json(struct check_opts opts);
int check_normal(struct check_opts opts);

int check(int argc, char *argv[]) {
  const char *short_opts = "hjt:d:";
  static struct option long_opts[] = {
    {"help", no_argument, NULL, 'h'},
    {"json", no_argument, NULL, 'j'},
    {"threads", required_argument, NULL, 't'},
    {"timeout", required_argument, NULL, 'd'},
    {NULL, no_argument, NULL, 0}
  };

  struct check_opts opts = {false};

  while(true) {
    int opt = getopt_long(argc, argv, short_opts, long_opts, NULL);

    if(opt < 0) break;

    switch(opt) {
      case 0: break;
      case 'h': opts.help = true; break;
      case 'j': opts.json = true; break;
      case 't':
        opts.threads = atoi(optarg);
        break;
      case 'd':
        opts.timeout = atoi(optarg);
        break;
      case '?':
      default:
        fprintf(stderr, "Error unrecognised: %s\n", argv[optind]);
        opts.help = true;
        break;
    }
  }

  if((optind + 2) != argc) {
  }

  if(opts.help) {
    return check_help(argv[0]);
  }

  if(opts.json) {
    return check_json(opts);
  }

  return check_normal(opts);
}

int check_help(const char *progname) {
  fprintf(
      stderr,
      "Checks problems.\n"
      "Usage: %s check [OPTIONS] [NUMBERS]\n\n"
      "OPTIONS\n"
      "  -h, --help       Show this help text.\n"
      "  -t, --threads n  Run with specified number of threads [not implemented].\n"
      "  -d, --timeout t  Count solutions as incorrect if they take longer than t ms.\n"
      "  -j, --json       Output as JSON.\n\n"
      "By default, all problems are checked. If problem numbers are specified as\n"
      "arguments, only the specified problems will be checked, in the order they\n"
      "appear.\n",
      progname);

  return EXIT_SUCCESS;
}

int check_json(struct check_opts opts) {
  json_t *results = json_array();
  bool has_error = false;

  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->solve) {
      json_t *jresult = json_object();
      json_object_set_new(jresult, "number", json_integer(problem->number));

      struct euler_result result = euler_solve(problem, NULL);
      bool correct = false;

      json_object_set_new(jresult, "error", json_boolean(!result.ok));

      // only check if there was no error.
      if(result.ok) {
        correct = euler_check(problem, &result);
        json_object_set_new(jresult, "correct", json_boolean(correct));
        json_object_set_new(jresult, "time", json_real(result.time));
      } else {
        has_error = true;
      }

      json_array_append_new(results, jresult);
    }
  }

  char *fmt = json_dumps(results, JSON_COMPACT);
  puts(fmt);
  free(fmt);
  json_decref(results);

  return EXIT_SUCCESS;
}

int check_normal(struct check_opts opts) {
  bool has_error = false;

  for(size_t i = 0; euler_problems[i]; i++) {
    const struct euler_problem *problem = euler_problems[i];

    if(problem->solve) {
      struct euler_result result = euler_solve(problem, NULL);
      bool correct = false;

      // only check if there was no error.
      if(result.ok) {
        correct = euler_check(problem, &result);

        // determine result.
        const char *res = "\033[0;32mcorrect\033[0m";

        if(!correct) {
          res = "\033[0;31mwrong\033[0m";
          has_error = true;
        }

        if(opts.timeout && (1000 * result.time) > opts.timeout) {
          res = "\033[0;31mtimeout\033[0m";
          has_error = true;
        }

        printf(
            "%03zu %s (\033[0;34m%.2fms\033[0m)\n",
            problem->number,
            res,
            result.time * 1000);
      } else {
        has_error = true;
        printf("%03zu \033[0;31merror\033[0m: %s\n", problem->number, result.result);
      }

    }
  }

  // return negative status code on error.
  if(has_error) {
    return -1;
  } else {
    return 0;
  }
}

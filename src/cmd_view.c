#include "euler.h"
#include "cmd.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <jansson.h>
#include <zlib.h>
#include <assert.h>

struct view_opts {
  bool help;
  bool json;
  size_t number;
};

int view_text(struct view_opts opts);
int view_help(const char *progname);

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
    view_help(argv[0]);
    return 0;
  }

  // parse requested number.
  opts.number = atoi(argv[optind + 1]);

  return view_text(opts);
}

int view_help(const char *progname) {
  return 0;
}

int print_uncompressed(const struct euler_problem *problem) {
  if(!problem->desc) {
    fprintf(stderr, "Error: Problem does not have a description.\n");
    return -1;
  }

  int ret;
  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;

  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    return ret;
  }

  strm.avail_in = problem->desc_len;
  strm.next_in = problem->desc;

  char outbuf[256];

  do {
    strm.avail_out = sizeof(outbuf);
    strm.next_out = outbuf;

    ret = inflate(&strm, Z_NO_FLUSH);
    assert(ret == Z_STREAM_END || ret == Z_OK);

    fwrite(outbuf, 1, sizeof(outbuf) - strm.avail_out, stdout);
  } while(strm.avail_out == 0);

  inflateEnd(&strm);

  return 0;
}

int view_text(struct view_opts opts) {
  const struct euler_problem *problem = euler_problem_get(opts.number);

  if(!problem) {
    fprintf(
        stderr,
        "Error: can't find problem %zu.\n",
        opts.number);
    return -1;
  }

  return print_uncompressed(problem);
}


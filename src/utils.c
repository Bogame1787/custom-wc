#include "utils.h"
#include <errno.h>
#include <string.h>
#include <stdlib.h>

void usage(const char *prog) {
    fprintf(stderr,
        "Usage: %s -d <dir> -p <threads>\n"
        "  -d    directory to recurse\n"
        "  -p    number of parallel threads\n", prog);
    exit(1);
}

void perror_msg(const char *msg, const char *arg) {
    fprintf(stderr, "%s(%s): %s\n", msg, arg, strerror(errno));
}
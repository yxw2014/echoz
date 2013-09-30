#include <errno.h>

#include <stdio.h>
#include <string.h>

void log_error(char *msg) {
    fprintf(stderr, "%s: error = %s\n", msg, strerror(errno));
}

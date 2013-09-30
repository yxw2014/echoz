#include "common.h"

int handle_echo(int sockfd) {
    char buf[BUFSIZE];
    int read_len = read(sockfd, buf, BUFSIZE);

    if ( read_len == -1 ) {
        log_error("read error");
    }
    else {
        int write_len = write(sockfd, buf, read_len);
        if ( write_len == -1 ) {
            log_error("write error");
        }
    }
}

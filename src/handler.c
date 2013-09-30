#include "common.h"

int handle_echo(int sockfd) {
    char buf[BUFSIZE];
    int nread = read(sockfd, buf, BUFSIZE);

    if ( nread == -1 ) {
        log_error("read error");
    }
    else {
        int nwrite = write(sockfd, buf, nread);
        if ( nwrite == -1 ) {
            log_error("write error");
        }
    }
}

#include "common.h"
#include "tcp_server.h"
#include "handler.h"

int main(int argc, char** argv) {
    char *bind_addr = "127.0.0.1";
    int port = 6666;

    int sockfd = tcp_server(bind_addr, port);
    if ( sockfd == ANET_ERR ) {
        return 1;
    }
    printf("bind to %s:%d\n", bind_addr, port);

    struct fd_set read_fdset;
    struct fd_set write_fdset;
    FD_ZERO(&read_fdset);
    FD_ZERO(&write_fdset);

    FD_SET(sockfd, &read_fdset);
    int nfds = sockfd + 1;

    char buf[FD_SETSIZE][BUFSIZE];
    int read_num[FD_SETSIZE];

    while ( 1 ) {
        int ready_fd_num = select(nfds, &read_fdset, &write_fdset, NULL, NULL);
        printf("select\n");

        if ( ready_fd_num == -1 ) {
            log_error("select error");
        }
        else {
            if ( FD_ISSET(sockfd, &read_fdset) ) {
                int cfd = accept(sockfd, NULL, NULL);
                printf("accept\n");

                if ( cfd == -1 ) {
                    log_error("accept error");
                }
                else {
                    FD_SET(cfd, &read_fdset);
                    printf("set cfd = %d to read_fdset\n", cfd);
                    if ( cfd >= nfds ) nfds = cfd + 1;
                }
            }

            for ( int fd = 0; fd < nfds; fd++ ) {
                printf("loop fd = %d\n", fd);
                if ( FD_ISSET(fd, &read_fdset) && fd != sockfd ) {
                    printf("in read fdset: fd = %d\n", fd);
                    if ( (read_num[fd] = read(fd, buf[fd], BUFSIZE)) == -1 ) {
                        log_error("read error");
                    }
                    else {
                        FD_CLR(fd, &read_fdset);
                        FD_SET(fd, &write_fdset);
                        printf("set fd = %d to write_fdset\n", fd);
                    }
                }
                if ( FD_ISSET(fd, &write_fdset) && fd != sockfd ) {
                    printf("in write fdset: fd = %d\n", fd);
                    if ( read_num[fd] > 0 ) {
                        if ( write(fd, buf[fd], read_num[fd]) == -1 ) {
                            log_error("write error");
                        }
                        FD_CLR(fd, &write_fdset);
                        close(fd);
                        read_num[fd] = 0;
                        printf("end fd = %d\n", fd);
                    }
                }
            }
        }
    }
}

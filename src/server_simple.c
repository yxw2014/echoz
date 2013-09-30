#include "common.h"
#include "tcp_server.h"
#include "handler.h"

int main(int argc, char** argv) {
    char *bind_addr = "127.0.0.1";
    int port = 6666;

    int sockfd = tcp_server(bind_addr, port);
    printf("bind to %s:%d\n", bind_addr, port);

    while ( 1 ) {
        int cfd = accept(sockfd, NULL, NULL);
        printf("accept\n");
        if ( cfd == -1 ) {
            log_error("accept error");
        }
        else {
            handle_echo(cfd);
        }
    }
}

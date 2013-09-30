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
        if ( cfd == -1 ) {
            log_error("accept error");
        }
        printf("accept\n");

        int pid = fork();
        if ( pid == -1 ) {
            log_error("fork failed");
            close(cfd);
        }
        else if ( pid == 0 ) {
            // child
            handle_echo(cfd);
            close(cfd);
        }
        else {
            // parent
        }
    }
}

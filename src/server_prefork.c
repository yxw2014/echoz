#include "common.h"
#include "tcp_server.h"
#include "handler.h"

int main(int argc, char** argv) {
    char *bind_addr = "127.0.0.1";
    int port = 6666;

    int sockfd = tcp_server(bind_addr, port);
    printf("bind to %s:%d\n", bind_addr, port);

    int i;
    for ( i = 0; i < 10; i++ ) {
        int pid = fork();
        if ( pid == -1 ) {
            log_error("fork failed");
        }
        else if ( pid == 0 ) {
            printf("forked, pid = %d\n", getpid());

            while ( 1 ) {
                int cfd = accept(sockfd, NULL, NULL);
                if ( cfd == -1 ) {
                    log_error("accept error");
                }
                printf("accept on %d\n", getpid());
                handle_echo(cfd);
                close(cfd);
            }
        }
    }
    // parent
    while ( i > 0 ) {
        waitpid(-1, NULL, 0);
        i--;
    }
}

#include "common.h"
#include "tcp_client.h"

int main(int argc, char** argv) {
    char *connect_addr = "127.0.0.1";
    int port = 6666;

    printf("connect to %s:%d\n", connect_addr, port);

    while ( 1 ) {
        int sockfd = tcp_client(connect_addr, port);
        if ( sockfd == ANET_ERR ) {
            break;
        }
        char buf[5] = "echo\0";
        int nwrite = write(sockfd, buf, 5);
        if ( nwrite == -1 ) {
            log_error("write error");
        }

        int nread = read(sockfd, buf, 5);
        if ( nread == -1 ) {
            log_error("read error");
        }
        printf("%s\n", buf);

        close(sockfd);
    }
}

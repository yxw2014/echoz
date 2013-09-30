#include "common.h"
#include "tcp_client.h"

int main(int argc, char** argv) {
    char *connect_addr = "127.0.0.1";
    int port = 6666;

    int sockfd = tcp_client(connect_addr, port);
    printf("connect to %s:%d\n", connect_addr, port);
}

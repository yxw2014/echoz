#include "common.h"

int tcp_client(char *connect_addr, int port) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

    if ( sockfd == -1 ) {
        log_error("socket creation error");
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( inet_aton(connect_addr, &sa.sin_addr) == 0 ) {
        log_error("invalid connect address");
        close(sockfd);
        return ANET_ERR;
    }

    if ( connect(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == -1 ) {
        log_error("connect error");
        close(sockfd);
        return ANET_ERR;
    }

    return sockfd;
}

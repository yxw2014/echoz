#include "common.h"

int tcp_server(char *bind_addr, int port) {
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

    if ( sockfd == -1 ) {
        log_error("socket creation error");
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if ( inet_aton(bind_addr, &sa.sin_addr) == 0 ) {
        log_error("invalid bind address");
        close(sockfd);
        return ANET_ERR;
    }

    if ( bind(sockfd, (struct sockaddr*)&sa, sizeof(sa)) == -1 ) {
        log_error("bind error");
        close(sockfd);
        return ANET_ERR;
    }

    if ( listen(sockfd, 511) == -1 ) {
        log_error("listen error");
        close(sockfd);
        return ANET_ERR;
    }

    return sockfd;
}

#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <string.h>

#define BUFSIZE 512
#define ANET_ERR 0

void log_error(char *msg);

#endif

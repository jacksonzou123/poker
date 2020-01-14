#ifndef NET_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 2048
#define MAX_QUEUE_SIZE 4

typedef fd_set FS;

void error_check(char *msg, int code);
void serve(const char *port);

#endif
#ifndef NET_H
#define NET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>

#define MAX_CLIENT_SIZE 12
#define MAX_BUFFER_SIZE 2048

// Utilities Functions
void error_check(const char *error_msg, const int error_code);

// Server Functions
void log(int f, char *buffer);

// Network Functions
void serve(const char *port);
void start_client(const char *hostname, const char *port);

#endif
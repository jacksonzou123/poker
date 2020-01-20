#ifndef NET_H
#define NET_H

#include "../poker/poker.h"

#include <errno.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>

#define MAX_CLIENT_SIZE 12
#define MAX_BUFFER_SIZE 2048

// Utilities Functions
void error_check(const char *error_msg, int error_code);

// Server Functions
void log_game(int f, const char *filename, char *buffer);

// Network Functions
void serve(int port, char *logname);
void start_client(char *hostname, int port);

#endif
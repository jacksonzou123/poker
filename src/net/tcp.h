#ifndef TCP_H
#define TCP_H

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT "8008"
#define TEST_IP "127.0.0.1"

void error_check(int, char *);

int server_setup();
int server_connect(int);
int client_setup(char *);

#endif
#ifndef TCP_H
#define TCP_H

#include "../utils/card.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT "8008"
#define TEST_IP "127.0.0.1"
#define PACKET_SIZE sizeof(deck)

typedef struct addrinfo ADDRINFO;
typedef struct sockaddr SOCKADDR;
typedef struct sockaddr_storage SOCKADDR_STORAGE;

void error_check(int, char *);

int server_setup();
int server_connect(int);
int client_setup(char *);

#endif
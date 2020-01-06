#ifndef TCP_H
#define TCP_H

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8000
#define MAX_PACKET_SIZE 4096

void make_socket(int, struct sockaddr_in);
void bind_socket(int, struct sockaddr_in);
void send_datagram(int, char *, struct sockaddr_in);
int recv_datagram(int, char *, char *, struct sockaddr_in);

#endif
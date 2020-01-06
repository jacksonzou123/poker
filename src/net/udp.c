#include "udp.h"

void make_socket(int sockfd, struct sockaddr_in addr)
{
  // Attempt to create socket file descriptor
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    printf("Socket Creation Error: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
  // Null a block of memory reserved for sockaddr_in struct
  memset(&addr, 0, sizeof(addr));
  // Fill in the server information
  addr.sin_family = AF_INET;
  addr.sin_port = htons(PORT);
  addr.sin_addr.s_addr = INADDR_ANY;
}

void bind_socket(int sockfd, struct sockaddr_in addr)
{
  // Attempt to bind socket with a network instance
  if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) < 0)
  {
    printf("Socket Binding Error: %s", strerror(errno));
    exit(EXIT_FAILURE);
  }
}

void send_datagram(int sockfd, char *data, struct sockaddr_in addr)
{
  // Send a char array
  sendto(sockfd, data, strlen(data), MSG_CONFIRM, (const struct sockaddr *)&addr, sizeof(addr));
}

int recv_datagram(int sockfd, char *data, char *buffer, struct sockaddr_in addr)
{
  socklen_t len = sizeof(addr);
  // Copy datagram char array into a buffer and return the length of datagram received
  return recvfrom(sockfd, buffer, MAX_PACKET_SIZE, MSG_WAITALL, (struct sockaddr *)&addr, &len);
}
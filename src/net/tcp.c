#include "tcp.h"

void error_check(int i, char *operation)
{
  if (i < 0)
  {
    printf("[%s] Error %d: %s\n", operation, errno, strerror(errno));
    exit(EXIT_FAILURE);
  }
}

int server_setup()
{
  int socket_descriptor, bind_error_code;

  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  error_check(socket_descriptor, "Server Socket");
  printf("[Server]: Socket Created\n");

  ADDRINFO *hints, *results;
  hints = (ADDRINFO *)calloc(1, sizeof(ADDRINFO));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_flags = AI_PASSIVE;
  getaddrinfo(NULL, PORT, hints, &results);

  bind_error_code = bind(socket_descriptor, results->ai_addr, results->ai_addrlen);
  error_check(bind_error_code, "Server Bind");
  printf("[Server]: Socket is listening...");

  free(hints);
  freeaddrinfo(results);
  return socket_descriptor;
}

int server_connect(int socket_descriptor)
{
  int client_socket;
  socklen_t socket_size;
  SOCKADDR_STORAGE client_address;

  socket_size = sizeof(client_address);
  client_socket = accept(socket_descriptor, (SOCKADDR *)&client_address, &socket_size);
  error_check(client_socket, "Server Accept");

  return client_socket;
}

int client_setup(char *server)
{
  int socket_descriptor, bind_error_code;

  socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
  error_check(socket_descriptor, "Client Socket");

  ADDRINFO *hints, *results;
  hints = (ADDRINFO *)calloc(1, sizeof(ADDRINFO));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  getaddrinfo(NULL, PORT, hints, &results);

  bind_error_code = bind(socket_descriptor, results->ai_addr, results->ai_addrlen);
  error_check(bind_error_code, "Client Connect");

  free(hints);
  freeaddrinfo(results);
  return socket_descriptor;
}
#include "tcp.h"

void subserver(int client_socket)
{
  DECK deck[1];
  while (read(client_socket, deck, PACKET_SIZE))
  {
    printf("[Subserver %d]: Received deck...\n", getpid());
    //wait(1);
    write(client_socket, deck, PACKET_SIZE);
  }
  close(client_socket);
  exit(EXIT_SUCCESS);
}

// int main()
// {
//   int listen_socket;
//   int fork_pid;
//   listen_socket = server_setup();
//
//   while (1)
//   {
//     int client_socket = server_connect(listen_socket);
//     fork_pid = fork();
//     if (!fork_pid)
//       subserver(client_socket);
//     else
//       close(client_socket);
//   }
// }

#include "net.h"

void start_client(const char *hostname, const char *port)
{
  /*
   * sent: Sent Message Flag
   * socketfd: Client Socket
   * serveraddr: Server Addr
   * server: Host Information
   * buffer: Message Buffer
   */
  int sent;
  int socketfd;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char buffer[MAX_BUFFER_SIZE];

  /*
   * Create the client socket.
   */
  error_check("Client Socket: Creation Error\n",
              (socketfd = socket(AF_INET, SOCK_STREAM, 0)));

  /*
   * Get the server's DNS entry.
   */
  if (!(server = gethostbyname(hostname)))
  {
    printf("%s: No Such Hostname Found!\n", hostname);
    fflush(stdout);
    exit(EXIT_FAILURE);
  }

  /*
   * Build the server's internet address.
   */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(port);

  /*
   * Connect to the server.
   */
  error_check("Client Socket: Connecting Failed\n",
              connect(socketfd, &serveraddr, sizeof(serveraddr)));

  /*
   * Send initial message to server.
   */
  printf("Enter a new message: ");
  bzero(buffer, MAX_BUFFER_SIZE);
  fgets(buffer, MAX_BUFFER_SIZE, stdin);
  error_check("Client Socket: Server Write Failed\n",
              write(socketfd, buffer, strlen(buffer)));
  sent = 1;
  bzero(buffer, MAX_BUFFER_SIZE);
  error_check("Client Socket: Server Read Failed\n",
              read(socketfd, buffer, MAX_BUFFER_SIZE));
  printf("Initial Server Response: %s\n", buffer);

  /*
   * Set to always listen from server.
   * Write to server on input.
   */
  while (1)
  {
    if (!sent)
    {
      bzero(buffer, MAX_BUFFER_SIZE);
      error_check("Client Socket: Server Read Failed\n",
                  read(socketfd, buffer, MAX_BUFFER_SIZE));
      printf("Server: %s\n", buffer);
      printf("Enter a new message: ");
      bzero(buffer, MAX_BUFFER_SIZE);
      if (fgets(buffer, MAX_BUFFER_SIZE, stdin))
      {
        if (!strcmp(buffer, "quit\n"))
        {
          buffer[strlen(buffer) - 1] = 0;
        }
        error_check("Client Socket: Server Write Failed\n",
                    write(socketfd, buffer, strlen(buffer)));
      }
      sent = 1;
    }

    if (!strlen(buffer) || !strcmp(buffer, "quit"))
    {
      close(socketfd);
      printf("Exiting...\n");
      fflush(stdout);
      exit(EXIT_SUCCESS);
    }

    bzero(buffer, MAX_BUFFER_SIZE);
    error_check("Client Socket: Server Read Failed\n",
                read(socketfd, buffer, MAX_BUFFER_SIZE));
    if (strlen(buffer))
    {
      printf("Server: %s\n", buffer);
    }
    sent = 0;
  }
}
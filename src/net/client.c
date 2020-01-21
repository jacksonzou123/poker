#include "net.h"

void start_client(const char *hostname, int port)
{
  /*
   * Prompt for player name.
   */
  char player[100];
  printf("Enter your player name: ");
  fgets(player, 100, stdin);

  /*
   * socketfd: Client Socket
   * serveraddr: Server Addr
   * server: Host Information
   * buffer: Message Buffer
   */
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
  bcopy((char *)server->h_addr_list[0], (char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(port);

  /*
   * Connect to the server.
   */
  error_check("Client Socket: Connecting Failed\n",
              connect(socketfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)));

  /*
   * Send initial message to server.
   */
  error_check("Client Socket: Server Write Failed\n",
              write(socketfd, player, strlen(player)));
  bzero(buffer, MAX_BUFFER_SIZE);
  error_check("Client Socket: Server Read Failed\n",
              read(socketfd, buffer, MAX_BUFFER_SIZE));
  printf("Initial Server Response: %s\n", buffer);

  printf("\e[1;1H\e[2J");

  /*
   * Set to always listen from server.
   * Write to server on input.
   */
  while (1)
  {
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

    while (strlen(buffer))
    {
      if (!strcmp("quit", buffer))
      {
        close(socketfd);
        printf("Player lost this session.\nExiting...\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      if (!strcmp("fold", buffer))
      {
        close(socketfd);
        printf("Player has choose to fold this session.\nExiting...\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      if (!strcmp("hlost", buffer))
      {
        close(socketfd);
        printf("House lost the game.\nPlease exit.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      if (!strcmp("hleft", buffer))
      {
        close(socketfd);
        printf("House left the game.\nPlease exit.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      if (!strcmp("hwon", buffer))
      {
        close(socketfd);
        printf("House won the game.\nPlease exit.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      if (!strcmp("win", buffer))
      {
        close(socketfd);
        printf("You won the game.\nPlease exit.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      printf("%s", buffer);
      fflush(stdout);
      bzero(buffer, MAX_BUFFER_SIZE);
    }

    printf("Enter a new message: ");
    fflush(stdout);
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
  }
}
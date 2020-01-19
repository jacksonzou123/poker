#include "net.h"

void log(int f, char *buffer)
{
  mode_t old_mask;
  old_mask = umask(0);
  error_check("I/O Operation: Open File Failed",
              (f = open("log.txt", O_CREAT | O_RDWR | O_APPEND, 0666)));
  buffer[strlen(buffer)] = '\n';
  write(f, buffer, strlen(buffer));
  close(f);
  umask(old_mask);
}

void serve(const char *port, const char *file)
{
  /*
   * f: File Descriptor
   * itr: Iterating Variable
   * opt: Flag Value for setsockopt
   * sendall: Send All Trigger
   * parentfd: Server Socket
   * maxsocketfd: Max Socket
   * itrsocketfd: Iterating Socket
   * currentfd: Current Client Socket
   * clientsocketlen: Byte Size of Client's Address
   * clientsfd: Array of Client Sockets
   * serveraddr: Server Addr
   * clientaddr: Client Addr
   * greet: Greeting Message On First Connection
   * readfds: Socket Set
   * buffer: Server Byte Buffer
   */
  int f, itr, opt, sendall;
  int parentfd, maxsocketfd, itrsocketfd, currentfd;
  int clientsocketlen;
  int clientsfd[MAX_CLIENT_SIZE];
  struct sockaddr_in serveraddr, clientaddr;
  const char greet[100] = "A connection is maded successfully.\0";
  char *buffer[MAX_BUFFER_SIZE];
  fd_set readfds;

  /*
   * Initialize the array of client sockets.
   */
  for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
  {
    clientsfd[itr] = 0;
  }

  /*
   * Initialize the server socket.
   */
  error_check("Server Socket: Creation Failed\n",
              (parentfd = socket(AF_INET, SOCK_STREAM, 0)));

  /*
   * Set server socket to accept multiple connections.
   */
  error_check("Server Socket: Set Socket Option Failed\n",
              setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt, sizeof(opt)));

  /*
   * Create the server's internet address.
   * Set the internet address to IPV4.
   * Set the IP address.
   * Set the listening port to a specified port.
   */
  bzero((char *)&serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons(port);

  /*
   * Bind the server socket to the specified port.
   * Set server to listen up to MAX_CLIENT_SIZE
   */
  error_check("Server Socket: Binding Socket Failed\n",
              bind(parentfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)));
  error_check("Server Socket: Set Listen Failed\n",
              listen(parentfd, MAX_CLIENT_SIZE));
  printf("Server: Listening on Port %s\n", port);
  fflush(stdout);

  /*
   * Set the client socket address length for looping.
   * Set sendall to false.
   */
  clientsocketlen = sizeof(clientaddr);
  sendall = 0;

  while (1)
  {
    /*
     * Zero out the socket set.
     * Add server socket to the socket set.
     * Copy the file descriptor from server socket to max socket.
     */
    FD_ZERO(&readfds);
    FD_SET(parentfd, &readfds);
    bzero((char *)&clientaddr, sizeof(clientaddr));
    currentfd = 0;
    maxsocketfd = parentfd;

    /*
     * Iterate through the array of client sockets:
     *  - Add socket to the socket set if it is valid.
     *  - Copy socket file descriptor to max socket file descriptor if
     *    the file descriptor is greater than the max socket file
     *    descriptor. 
     */
    for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
    {
      itrsocketfd = clientsfd[itr];
      if (itrsocketfd > 0)
      {
        FD_SET(itrsocketfd, &readfds);
      }
      if (itrsocketfd > maxsocketfd)
      {
        maxsocketfd = itrsocketfd;
      }
    }

    /*
     * Wait for a connection request.
     */
    error_check("Server: Error in Select\n",
                select(maxsocketfd + 1, &readfds, 0, 0, 0));

    /*
     * If there is an incoming connection:
     *  - Accept the incoming connection.
     *  - Print information about the new connection.
     *  - Greet the new client.
     *  - Read from client to make sure "quit" is not emitted.
     *  - Add the client to the array of client sockets.
     */
    if (FD_ISSET(parentfd, &readfds))
    {
      error_check("Server: Accepting Client Failed\n",
                  (currentfd = accept(parentfd, (struct sockaddr *)&clientaddr,
                                      (socklen_t *)&clientsocketlen)));

      printf("New connection, socket fd is %d, IP is: %s, port: %d\n ",
             currentfd, inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

      error_check("Server: Send Greeting Failed\n",
                  send(currentfd, greet, strlen(greet), 0));

      bzero(buffer, MAX_BUFFER_SIZE);
      if (read(currentfd, buffer, MAX_BUFFER_SIZE))
      {
        if (!strcmp(buffer, "quit"))
        {
          close(currentfd);
          printf("Socket %d has disconnected.\n", currentfd);
          fflush(stdout);
        }
        else
        {
          log(f, buffer);
          sendall = 1;

          for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
          {
            itrsocketfd = clientsfd[itr];
            if (!itrsocketfd)
            {
              clientsfd[itr] = currentfd;
              printf("Added socket %d to the array of client sockets at %d\n", currentfd, itr);
              break;
            }
          }
        }
      }
    }

    /*
     * Perform I/O operations on all current stored sockets:
     *  - If a socket in the set is hot, read the socket:
     *    - If "quit" is emitted, set buffer to "A socket has disconnected.\n\0".
     *    - Else, log the emitted message and set the server to send the message to all.
     */
    for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
    {
      itrsocketfd = clientsfd[itr];
      if (FD_ISSET(itrsocketfd, &readfds))
      {
        bzero(buffer, MAX_BUFFER_SIZE);
        if (read(itrsocketfd, buffer, MAX_BUFFER_SIZE))
        {
          if (!strcmp(buffer, "quit"))
          {
            close(itrsocketfd);
            printf("Socket %d has disconnected.\n", clientsfd[itr]);
            fflush(stdout);
            sendall = 1;
            bzero(buffer, MAX_BUFFER_SIZE);
            strcpy(buffer, "A socket has disconnected.\n\0");
            clientsfd[itr] = 0;
            break;
          }
          else
          {
            log(f, buffer);
            sendall = 1;
            break;
          }
        }
      }
    }

    /*
     *  If send all is set to true,
     *  the server send the last accepted message to all clients.
     */
    if (sendall)
    {
      for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
      {
        itrsocketfd = clientsfd[itr];
        if (itrsocketfd)
        {
          error_check("Server: Checking In Failed\n",
                      send(itrsocketfd, buffer, strlen(buffer), 0));
        }
      }
    }

    /*
     * Reset send all flag to false.
     */
    sendall = 0;
  }
}
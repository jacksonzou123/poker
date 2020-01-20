#include "net.h"

void serve(const char *port, const char *logname)
{
  /*
   * Prompt the user for their player name.
   */
  char dealer[100];
  printf("Please enter your player name: ");
  fgets(dealer, 100, stdin);

  dealer[strlen(dealer) - 1] = 0;

  /*
   * Create a 52-card deck.
   */
  int deck_pos = 0;
  int cards_out = 0;
  CARD **full_deck = get_cards();
  CARD ***players_cards = malloc(sizeof(CARD **));

  /*
   * Game Setup
   */
  int game_setup = 1;
  int total = 0;
  int conn = 0;
  int num_player = 1;
  char **players = (char **)malloc(sizeof(char *) * num_player);

  players[num_player - 1] = (char *)malloc(100);
  strncpy(players[num_player - 1], dealer, 100);

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
  const char greet[100] = "User has joined the session.\0";
  char buffer[MAX_BUFFER_SIZE];
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
   * Initialize f file descriptor to 0.
   */
  clientsocketlen = sizeof(clientaddr);
  sendall = 0;
  f = 0;

  while (1)
  {
    /*
     * Zero out the socket set.
     * Add server socket to the socket set.
     * Copy the file descriptor from server socket to max socket.
     */
    FD_ZERO(&readfds);
    FD_SET(parentfd, &readfds);
    FD_SET(0, &readfds);
    bzero((char *)&clientaddr, sizeof(clientaddr));
    currentfd = 0;
    maxsocketfd = parentfd;
    conn = 0;

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

    for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
    {
      if (!game_setup)
      {
        if (clientsfd[itr])
        {
          conn++;
        }
      }
    }

    if (!game_setup)
    {
      if (!conn)
      {
        printf("No other players are connected. You won!\n");
        fflush(stdout);
        exit(EXIT_FAILURE);
      }
    }
    else
    {
      printf("Server: ");
      fflush(stdout);
    }

    /*
     * Wait for a connection request.
     */
    if (game_setup)
    {
      error_check("Server: Error in Select\n",
                  select(maxsocketfd + 1, &readfds, 0, 0, 0));
    }

    if (game_setup)
    {
      if (FD_ISSET(0, &readfds))
      {
        bzero(buffer, MAX_BUFFER_SIZE);
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        buffer[strlen(buffer) - 1] = 0;

        if (!strcmp(buffer, "finish setup") && game_setup)
        {
          game_setup = 0;
          sendall = 1;
          printf("\e[1;1H\e[2J");
          printf("The game has begun.\n");
          printf("-------------------\n");
          fflush(stdout);
        }
        if (!strcmp(buffer, "quit"))
        {
          printf("%s\n", buffer);
          fflush(stdout);
          exit(EXIT_SUCCESS);
        }
      }
    }

    /*
     * If there is an incoming connection:
     *  - Accept the incoming connection.
     *  - Print information about the new connection.
     *  - Greet the new client.
     *  - Read from client to make sure "quit" is not emitted.
     *  - Add the client to the array of client sockets.
     */
    if (game_setup)
    {
      if (FD_ISSET(parentfd, &readfds))
      {
        error_check("Server: Accepting Client Failed\n",
                    (currentfd = accept(parentfd, (struct sockaddr *)&clientaddr,
                                        (socklen_t *)&clientsocketlen)));

        printf("New connection, socket fd is %d, IP is: %s, port: %d\n\t",
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
            total++;
            buffer[strlen(buffer) - 1] = 0;
            players = (char **)realloc(players, sizeof(char *) * ++num_player);
            players[num_player - 1] = (char *)malloc(100);
            strncpy(players[num_player - 1], buffer, 100);

            players_cards = realloc(players_cards, sizeof(CARD **) * num_player);

            log_game(f, logname, buffer);

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
    }

    /*
     *  If send all is set to true,
     *  the server send the last accepted message to all clients.
     */
    if (!game_setup)
    {
      if (total == 0)
      {
        printf("No player left. You have won.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
      char name_buf[100];
      cards_out++;
      bzero(buffer, MAX_BUFFER_SIZE);
      for (itr = 0; itr < num_player; itr++)
      {
        players_cards[itr] = realloc(players_cards[itr], sizeof(CARD *) * cards_out);
        players_cards[itr][cards_out - 1] = full_deck[deck_pos++];
      }
      int i2;
      for (itr = 0; itr < num_player; itr++)
      {
        int sum = 0;
        for (i2 = 0; i2 < cards_out; i2++)
        {
          sum += players_cards[itr][i2]->num;
        }
        if (sum == 21)
        {
          if (itr > 0)
          {
            char win_buf[10] = "win";
            error_check("Server: Checking In Failed\n",
                        send(clientsfd[itr - 1], win_buf, 10, 0));
          }
          else
          {
            for (i2 = 0; i2 < MAX_CLIENT_SIZE; i2++)
            {
              char house_won[10] = "hwon";
              itrsocketfd = clientsfd[i2];
              if (itrsocketfd)
              {
                clientsfd[i2] = 0;
                error_check("Server: Checking In Failed\n",
                            send(itrsocketfd, house_won, 10, 0));
                close(itrsocketfd);
              }
            }
            int n;
            for (n = 0; n < num_player; n++)
            {
              if ((n > 0) && (clientsfd[n - 1] != 0))
              {
                bzero(name_buf, 100);
                sprintf(name_buf, "Player %s: ", players[n]);
                strcat(buffer, name_buf);
                players_cards[n] = realloc(players_cards[n], sizeof(CARD *) * cards_out);
                players_cards[n][cards_out - 1] = full_deck[deck_pos++];
                strcat(buffer, stringify_cards(players_cards[n], cards_out));
                strcat(buffer, "\n");
              }
              else if (n == 0)
              {
                bzero(name_buf, 100);
                sprintf(name_buf, "Player %s: ", players[n]);
                strcat(buffer, name_buf);
                players_cards[n] = realloc(players_cards[n], sizeof(CARD *) * cards_out);
                players_cards[n][cards_out - 1] = full_deck[deck_pos++];
                strcat(buffer, stringify_cards(players_cards[n], cards_out));
                strcat(buffer, "\n");
              }
            }
            printf("You have won!\n");
            fflush(stdout);
            exit(EXIT_SUCCESS);
          }
        }
        if (sum > 21)
        {
          printf("%s", buffer);
          fflush(stdout);
          if (itr > 0)
          {
            char q_buf[10] = "quit";
            error_check("Server: Checking In Failed\n",
                        send(clientsfd[itr - 1], q_buf, 10, 0));
            total--;
          }
          else
          {
            for (i2 = 0; i2 < MAX_CLIENT_SIZE; i2++)
            {
              char house_lost[10] = "hlost";
              itrsocketfd = clientsfd[i2];
              if (itrsocketfd)
              {
                clientsfd[i2] = 0;
                error_check("Server: Checking In Failed\n",
                            send(itrsocketfd, house_lost, 10, 0));
                close(itrsocketfd);
              }
            }
            int n;
            for (n = 0; n < num_player; n++)
            {
              if ((n > 0) && (clientsfd[n - 1] != 0))
              {
                bzero(name_buf, 100);
                sprintf(name_buf, "Player %s: ", players[n]);
                strcat(buffer, name_buf);
                players_cards[n] = realloc(players_cards[n], sizeof(CARD *) * cards_out);
                players_cards[n][cards_out - 1] = full_deck[deck_pos++];
                strcat(buffer, stringify_cards(players_cards[n], cards_out));
                strcat(buffer, "\n");
              }
              else if (n == 0)
              {
                bzero(name_buf, 100);
                sprintf(name_buf, "Player %s: ", players[n]);
                strcat(buffer, name_buf);
                players_cards[n] = realloc(players_cards[n], sizeof(CARD *) * cards_out);
                players_cards[n][cards_out - 1] = full_deck[deck_pos++];
                strcat(buffer, stringify_cards(players_cards[n], cards_out));
                strcat(buffer, "\n");
              }
            }
            printf("%s\n", buffer);
            printf("You have lost!\n");
            fflush(stdout);
            exit(EXIT_SUCCESS);
          }
        }
      }
      for (itr = 0; itr < num_player; itr++)
      {
        if ((itr > 0) && (clientsfd[itr - 1] != 0))
        {
          bzero(name_buf, 100);
          sprintf(name_buf, "Player %s: ", players[itr]);
          strcat(buffer, name_buf);
          players_cards[itr] = realloc(players_cards[itr], sizeof(CARD *) * cards_out);
          players_cards[itr][cards_out - 1] = full_deck[deck_pos++];
          strcat(buffer, stringify_cards(players_cards[itr], cards_out));
          strcat(buffer, "\n");
        }
        else if (itr == 0)
        {
          bzero(name_buf, 100);
          sprintf(name_buf, "Player %s: ", players[itr]);
          strcat(buffer, name_buf);
          players_cards[itr] = realloc(players_cards[itr], sizeof(CARD *) * cards_out);
          players_cards[itr][cards_out - 1] = full_deck[deck_pos++];
          strcat(buffer, stringify_cards(players_cards[itr], cards_out));
          strcat(buffer, "\n");
        }
      }
      printf("%s", buffer);
      fflush(stdout);
      for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
      {
        itrsocketfd = clientsfd[itr];
        if (itrsocketfd)
        {
          error_check("Server: Checking In Failed\n",
                      send(itrsocketfd, buffer, MAX_BUFFER_SIZE, 0));
        }
      }
      for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
      {
        itrsocketfd = clientsfd[itr];
        if (itrsocketfd)
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
              char q_buf[10] = "fold";
              log_game(f, logname, buffer);
              sendall = 1;
              if (!strcmp(buffer, "fold\n\n"))
              {
                error_check("Server: Checking In Failed\n",
                            send(itrsocketfd, q_buf, 10, 0));
                close(itrsocketfd);
                printf("Player %d has disconnected.\n", itr + 1);
                fflush(stdout);
                clientsfd[itr] = 0;
                total--;
                if (!total)
                {
                  printf("No players beside house left.\n");
                  fflush(stdout);
                  exit(EXIT_SUCCESS);
                }
              }
            }
          }
        }
      }
      bzero(buffer, MAX_BUFFER_SIZE);
      printf("Server: ");
      fflush(stdout);
      fgets(buffer, MAX_BUFFER_SIZE, stdin);
      if (!strcmp(buffer, "quit\n"))
      {
        for (itr = 0; itr < MAX_CLIENT_SIZE; itr++)
        {
          itrsocketfd = clientsfd[itr];
          if (itrsocketfd)
          {
            char hleft[10] = "hleft";
            clientsfd[itr] = 0;
            error_check("Server: Checking In Failed\n",
                        send(itrsocketfd, hleft, 10, 0));
            close(itrsocketfd);
          }
        }
        printf("You have quit the game.\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
      }
    }

    /*
     * Reset send all flag to false.
     */
  }
}
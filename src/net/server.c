#include "net.h"

void error_check(char *msg, int code)
{
  if (code < 0)
  {
    perror(msg);
    exit(EXIT_FAILURE);
  }
}

void serve(const char *port)
{
  int parentfd, childfd;
  int clientlen;
  struct sockaddr_in serveraddr, clientaddr;
  char buf[BUFSIZE];

  int optval = 1; /* flag value for setsockopt */
  int notdone = 1;

  FS readfds;

  /* 
   * socket: create the parent socket 
   */
  error_check("ERROR opening socket",
              (parentfd = socket(AF_INET, SOCK_STREAM, 0)));

  /* 
   * setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *)&serveraddr, sizeof(serveraddr));

  /* 
   * -----------
   * server addr
   * -----------
   * 
   * this is an Internet address 
   * let the system figure out our IP address 
   * this is the port we will listen on 
   * 
   */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)atoi(port));

  /* 
   * bind parent socket to port
   */
  error_check("ERROR on binding",
              bind(parentfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)));

  /*
   * listening to parent socket 
   * allow MAX_QUEUE_SIZE requests to queue
   */
  error_check("ERROR on listen",
              listen(parentfd, MAX_QUEUE_SIZE));

  /* 
   * initialize some things for the main loop
   */
  clientlen = sizeof(clientaddr);
  printf("server> ");
  fflush(stdout);

  /* 
   * main loop: wait for connection request or stdin command.
   *
   * If connection request -> then echo input line and close connection. 
   * If command -> process command.
   */
  while (notdone)
  {

    /* 
     * initialize the fd set
     * add socket fd
     * add stdin fd (0)
     * 
     * select: check stdin or received connection request
     * 
     */
    FD_ZERO(&readfds);
    FD_SET(parentfd, &readfds);
    FD_SET(0, &readfds);
    error_check("ERROR in select",
                select(parentfd + 1, &readfds, 0, 0, 0));

    /* 
     * commands from stdin:
     * "c<nl>"  print the number of connection requests
     * "q<nl>"  quit the server 
     * if the user has entered a command, process it 
     */
    if (FD_ISSET(0, &readfds))
    {
      fgets(buf, BUFSIZE, stdin);
      switch (buf[0])
      {
      case 'q':
        notdone = 0;
        break;
      default:
        printf("ERROR: Unknown Command\nserver> ");
        fflush(stdout);
      }
    }

    /* if a connection request has arrived, process it */
    if (FD_ISSET(parentfd, &readfds))
    {
      printf("Received a connection request.\nserver> ");
      fflush(stdout);

      /* 
       * accept: wait for a connection request 
       */
      error_check("ERROR on accept",
                  (childfd = accept(parentfd, (struct sockaddr *)&clientaddr, &clientlen)));

      /* 
       * read: read input string from the client
       */
      bzero(buf, BUFSIZE);
      error_check("ERROR reading from socket",
                  read(childfd, buf, BUFSIZE));

      /* 
       * write: echo the input string back to the client 
       */
      error_check("ERROR writing to socket",
                  write(childfd, buf, strlen(buf)));

      close(childfd);
    }
  }

  /* clean up */
  printf("Terminating server.\n");
  close(parentfd);
  exit(EXIT_SUCCESS);
}
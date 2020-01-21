#include "net/net.h"

#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  int portno;
  int child_status;

  printf("Run ./Poker --help for more instructions.\n\n");

  if (argc < 2)
  {
    printf("Usage: <server|client> <port> <CLIENT_ONLY:hostname>\n");
  }
  else if (!argv[1] && !argv[2])
  {
    printf("Usage: <server|client> <port> <CLIENT_ONLY:hostname>\n");
  }
  else if (!strcmp(argv[1], "--help"))
  {
    if (!(fork()))
    {
      char *args[] = {"less", "HELP.md", 0};

      execvp(args[0], args);
      fprintf(stderr, "Failed to execute %s\n", args[0]);
      exit(EXIT_FAILURE);
    }
    else
    {
      wait(&child_status);
      printf("\e[1;1H\e[2J");
      printf("To see the instruction again, use ./Poker --help\n");
      return 0;
    }
  }
  else
  {
    if (!strcmp(argv[1], "server") && argv[2])
    {
      sscanf(argv[2], "%d", &portno);
      if (!(fork()))
      {
        serve(portno, "log.txt");
      }
      else
      {
        wait(&child_status);

        char *args2[] = {"cat", "log.txt", 0};

        printf("\e[1;1H\e[2J");
        printf("\nGame Log\n");
        execvp(args2[0], args2);
        printf("Thank you for playing.\n");

        return 0;
      }
    }
    if (!strcmp(argv[1], "client") && argv[2] && argv[3])
    {
      sscanf(argv[2], "%d", &portno);
      if (!(fork()))
      {
        start_client(argv[3], portno);
      }
      else
      {
        wait(&child_status);
        printf("Thank you for playing.\n");
        return 0;
      }
    }
    else
    {
      printf("Usage: <server|client> <port> <CLIENT_ONLY:hostname>\n");
    }
  }
  return 0;
}

#include "net/net.h"
#include "poker/poker.h"

#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  int child_status;
  int portno;

  if (argv < 2)
  {
    printf("Usage: <server|client> <port> <?|hostname>\n");
  }
  else if (!argv[1] || !argv[2] || !argv[3])
  {
    printf("Usage: <server|client> <port> <?|hostname>\n");
  }
  else
  {
    sscanf(argv[2], "%d", &portno);
    if (!strcmp(argv[1], "server"))
    {
      if (!(fork()))
      {
        serve(portno, "log.txt");
      }
      else
      {
        wait(&child_status);
        printf("Thank you for playing.\n");
      }
    }
    else if (!strcmp(argv[1], "client"))
    {
      if (!(fork()))
      {
        start_client(argv[3], portno);
      }
      else
      {
        wait(&child_status);
        printf("Thank you for playing.\n");
      }
    }
  }
  return 0;
}

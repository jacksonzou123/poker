#include "net/net.h"
#include "poker/poker.h"

#include <string.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  pid_t cpid;
  int child_status;
  char buffer[10];

  printf("Welcome to Multiplayer Poker!\n");
  printf("-----------------------------\n\n");
  printf("Options\n");
  printf("* serve\n");
  printf("* client\n");
  printf("\nStart Option: ");

  fgets(buffer, 10, stdin);
  buffer[strlen(buffer) - 1] = 0;

  if (!strcmp(buffer, "serve"))
  {
    serve("8000", "log.txt");
  }
  else if (!strcmp(buffer, "client"))
  {
    start_client("127.0.0.1", "8000");
  }
  return 0;
}

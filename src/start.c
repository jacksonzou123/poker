#include "net/net.h"
#include "poker/poker.h"

int main(int argc, char const *argv[])
{
  int pid, cpid;

  if (argc < 2)
  {
    printf("usage: Poker <server|client>\n");
    exit(EXIT_FAILURE);
  }

  if (!strcmp(argv[1], "server"))
  {
    if (!(pid = fork()))
    {
      serve("8000");
    }
    if (!(cpid = fork()))
    {
      // server_init_poker();
    }
  }
  else if (!strcmp(argv[1], "client"))
  {
    if (!(pid = fork()))
    {
      start_client("127.0.0.1", "8000");
    }
    if (!(cpid = fork()))
    {
      // client_init_poker();
    }
  }
  return 0;
}

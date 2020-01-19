#include "net/net.h"

int main(int argc, char const *argv[])
{
  if (argc < 2)
  {
    printf("Invalid Arguments\n");
    exit(EXIT_FAILURE);
  }
  if (!strcmp(argv[1], "server"))
  {
    serve("8000");
  }
  else if (!strcmp(argv[1], "client"))
  {
    start_client("127.0.0.1", "8000");
  }
  return 0;
}

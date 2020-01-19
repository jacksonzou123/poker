#include "net.h"

void error_check(const char *error_msg, const int error_code)
{
  if (error_code < 0)
  {
    perror(error_msg);
    exit(EXIT_FAILURE);
  }
}
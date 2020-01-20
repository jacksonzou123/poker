#include "net.h"

void error_check(const char *error_msg, int error_code)
{
  if (error_code < 0)
  {
    perror(error_msg);
    exit(EXIT_FAILURE);
  }
}

void log_game(int f, const char *filename, char *buffer)
{
  mode_t old_mask;
  old_mask = umask(0);
  error_check("I/O Operation: Open File Failed",
              (f = open(filename, O_CREAT | O_RDWR | O_APPEND, 0666)));
  buffer[strlen(buffer)] = '\n';
  write(f, buffer, strlen(buffer));
  close(f);
  umask(old_mask);
}
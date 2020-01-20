#include "poker.h"

void server_init_poker(char *dealer)
{
  int i, j = 1, f;
  mode_t old_mask;
  CARD **full_deck = get_cards();
  char buf_a[BUFFER_SIZE], buf_b[BUFFER_SIZE];
  char **players = malloc(sizeof(PLAYER *));
  players[j - 1] = dealer;

  mkfifo(SERVER_PIPE, 0666);

  old_mask = umask(0);

  f = open(SERVER_PIPE, O_WRONLY);
  write(f, full_deck, BUFFER_SIZE);
  close(f);

  f = open(SERVER_PIPE, O_RDONLY);
  while (read(f, buf_b, BUFFER_SIZE))
  {
    if (strcmp(buf_b, ""))
    {
      players = realloc(players, sizeof(players) * ++j);
      players[j - 1] = buf_b;
    }
  }
  close(f);

  umask(old_mask);

  PLAYER **all_players = malloc(i * sizeof(PLAYER *));

  for (i = 0; i < j - 1; i++)
  {
    all_players[i] = init_player(players[i]);
  }

  while (1)
  {
    old_mask = umask(0);

    f = open(SERVER_PIPE, O_WRONLY);
    // Do Something
    write(f, buf_a, BUFFER_SIZE);
    close(f);

    f = open(SERVER_PIPE, O_RDONLY);
    read(f, buf_b, BUFFER_SIZE);
    // Do Something
    close(f);

    umask(old_mask);
  }
}

void client_init_poker(char *player)
{
  mode_t old_mask;
  int f;
  char buf_a[BUFFER_SIZE], buf_b[BUFFER_SIZE];

  mkfifo(CLIENT_PIPE, 0666);

  old_mask = umask(0);

  f = open(CLIENT_PIPE, O_WRONLY);
  strncpy(buf_a, player, BUFFER_SIZE);
  write(f, buf_a, BUFFER_SIZE);
  close(f);

  f = open(CLIENT_PIPE, O_RDONLY);
  read(f, buf_b, BUFFER_SIZE);
  if (strcmp(buf_b, "SUCCESS"))
  {
    exit(EXIT_FAILURE);
  }
  close(f);

  umask(old_mask);

  while (1)
  {
    old_mask = umask(0);

    f = open(CLIENT_PIPE, O_WRONLY);
    // Do Something
    write(f, buf_a, BUFFER_SIZE);
    close(f);

    f = open(CLIENT_PIPE, O_RDONLY);
    read(f, buf_b, BUFFER_SIZE);
    // Do Something
    close(f);

    umask(old_mask);
  }
}
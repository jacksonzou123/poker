#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>

typedef struct player
{
  char player_name[100];
  int player_amount;
} PLAYER;

PLAYER *init_player(char *player_name);

#endif
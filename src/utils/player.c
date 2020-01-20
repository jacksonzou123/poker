#include "player.h"

PLAYER *init_player(char *player_name)
{
  PLAYER *player = malloc(sizeof(PLAYER));

  strncpy(player->player_name, player_name, 100);
  player->player_amount = 1000;

  return player;
}
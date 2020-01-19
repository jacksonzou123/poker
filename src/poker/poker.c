#include "poker.h"

void server_init_poker(char **players, int player_num)
{
  CARD **deck = get_cards(player_num);

  HAND **player_hands = dist_cards(players, player_num, deck, 5 + (player_num * 2));
  BOARD *board = fill_board(deck);

  // int i;
  // for (i = 0; i < 13; i++)
  // {
  //   print_card(deck[i]);
  // }

  free(deck);
  free(player_hands);
  free(board);
}

void client_init_poker(char *player_name)
{
}
#include "util.h"

HAND *make_hand(char *player_name, CARD *a, CARD *b)
{
  HAND *new_hand = malloc(sizeof(HAND));
  strncpy(new_hand->player, player_name, 100);
  new_hand->card_a = a;
  new_hand->card_b = b;
  return new_hand;
}

HAND **dist_cards(char **player_names, int num_players, CARD **cards, int num_cards)
{
  int i, j = num_cards - 1, k = 0;
  CARD *a, *b;
  HAND **player_cards = malloc(num_players * 2 * sizeof(void *));

  for (int i = 0; i < num_players; i++)
  {
    a = cards[j--];
    b = cards[j--];
    player_cards[k++] = make_hand(player_names[i], a, b);
  }

  return player_cards;
}
#include "util.h"

char *num_to_suit(int card)
{
  switch (card / 13)
  {
  case 0:
    return "club";
  case 1:
    return "diamond";
  case 2:
    return "heart";
  default:
    return "spade";
  }
}

CARD **get_cards(int player_num, int num_cards)
{
  srand(time(0));

  CARD *empty_deck[] = malloc(player_num * sizeof(void *));

  int cards[FULL_DECK_SIZE];
  int card, choice;
  for (card = 0; card < FULL_DECK_SIZE; card++)
  {
    cards[card] = card;
  }

  for (card = FULL_DECK_SIZE - 1; card > 1; card--)
  {
    choice = rand() % card;

    int temp = cards[card];
    cards[card] = cards[choice];
    cards[choice] = temp;
  }

  for (card = 0; card < num_cards; card++)
  {
    empty_deck[card] = malloc(sizeof(CARD));
    char *suit_num = num_to_suit(cards[card]);
    strncpy(empty_deck[card]->suit, suit_num, 10);
    empty_deck[card]->num = cards[card] % 13;
  }

  return empty_deck
}

void print_card(CARD *input)
{
  if (input->num > 1 || input->num <= 10)
  {
    printf("%d of ", input->num);
  }
  else
  {
    switch (input->num)
    {
    case 1:
      printf("Ace of ");
      break;
    case 9:
      printf("Jack of ");
      break;
    case 10:
      printf("Queen of ");
      break;
    case 11:
      printf("King of ");
      break;
    }
  }
  printf("%s\n", input->suit);
}
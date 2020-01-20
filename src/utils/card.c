#include "util.h"

char *num_to_suit(int card)
{
  switch (card / 13)
  {
  case 0:
    return "diamond";
  case 1:
    return "club";
  case 2:
    return "heart";
  default:
    return "spade";
  }
}

int card_to_num(CARD *card)
{
  if (!strcmp("diamond", card->suit))
  {
    return card->num;
  }
  if (!strcmp("club", card->suit))
  {
    return card->num + 13;
  }
  if (!strcmp("heart", card->suit))
  {
    return card->num + 26;
  }
  if (!strcmp("spade", card->suit))
  {
    return card->num + 39;
  }
  return 0;
}

CARD **get_cards(int player_num)
{
  srand(time(0));

  CARD **empty_deck = (CARD **)malloc(((player_num * 2) + 5) * sizeof(CARD *));

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

  for (card = 0; card < ((player_num * 2) + 5); card++)
  {
    empty_deck[card] = malloc(sizeof(CARD));
    char *suit_num = num_to_suit(cards[card]);
    strncpy(empty_deck[card]->suit, suit_num, 10);
    empty_deck[card]->num = cards[card] % 13;
  }

  return empty_deck;
}

int compare_card(CARD *a, CARD *b)
{
  return card_to_num(a) - card_to_num(b);
}

void print_card(CARD *input)
{
  if (input->num < 9)
  {
    printf("%d of ", input->num + 2);
  }
  else
  {
    switch (input->num)
    {
    case 9:
      printf("Jack of ");
      break;
    case 10:
      printf("Queen of ");
      break;
    case 11:
      printf("King of ");
      break;
    case 12:
      printf("Ace of ");
      break;
    }
  }
  printf("%s\n", input->suit);
}
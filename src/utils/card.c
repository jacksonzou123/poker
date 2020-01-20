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

CARD **get_cards()
{
  srand(time(0));

  CARD **empty_deck = (CARD **)malloc(52 * sizeof(CARD *));

  int cards[FULL_DECK_SIZE];
  int card, choice;
  for (card = 0; card < FULL_DECK_SIZE; card++)
  {
    cards[card] = card + 1;
  }

  for (card = FULL_DECK_SIZE - 1; card > 1; card--)
  {
    choice = rand() % card;

    int temp = cards[card];
    cards[card] = cards[choice];
    cards[choice] = temp;
  }

  for (card = 0; card < 52; card++)
  {
    empty_deck[card] = malloc(sizeof(CARD));
    char *suit_num = num_to_suit(cards[card]);
    strncpy(empty_deck[card]->suit, suit_num, 10);
    empty_deck[card]->num = cards[card] % 13;
  }

  return empty_deck;
}

int sum_card(int count, ...)
{
  int i, sum = 0;
  va_list card_nums;

  va_start(card_nums, count);
  for (i = 0; i < count; i++)
  {
    sum += va_arg(card_nums, int);
  }
  va_end(card_nums);

  return sum;
}

void print_card(CARD *input)
{
  if (input->num < 10)
  {
    printf("%d of ", input->num + 1);
  }
  else
  {
    switch (input->num)
    {
    case 10:
      printf("Jack of ");
      break;
    case 11:
      printf("Queen of ");
      break;
    case 12:
      printf("King of ");
      break;
    case 13:
      printf("Ace of ");
      break;
    }
  }
  printf("%s", input->suit);
}

char *stringify_cards(CARD **deck, int n)
{
  int i;
  char *buffer = malloc(1024);
  char card[25];

  for (i = 0; i < n; i++)
  {
    bzero(card, 25);

    if (deck[i]->num < 10)
    {
      sprintf(card, "%d of %s | ", deck[i]->num + 1, deck[i]->suit);
    }
    else
    {
      switch (deck[i]->num)
      {
      case 10:
        sprintf(card, "Jack of %s | ", deck[i]->suit);
        break;
      case 11:
        sprintf(card, "Queen of %s | ", deck[i]->suit);
        break;
      case 12:
        sprintf(card, "King of %s | ", deck[i]->suit);
        break;
      case 13:
        sprintf(card, "Ace of %s | ", deck[i]->suit);
        break;
      }
    }

    strcat(buffer, card);
  }

  return buffer;
}
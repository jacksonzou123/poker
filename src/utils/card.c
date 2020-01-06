#include "card.h"

void build_deck(CARD *deck[])
{
  int i, j, k = 0;

  char suits[4] = "dchs";

  for (i = 0; i < 4; i++)
  {
    for (j = 0; j < 13; j++)
    {
      CARD *card = malloc(sizeof(CARD));
      card->suit = suits[i];
      card->num = j + 1;
      deck[k++] = card;
    }
  }
}

void swap(CARD *a, CARD *b)
{
  CARD temp = *a;
  *a = *b;
  *b = temp;
}

void shuffle(CARD *deck[], int n)
{
  srand(time(0));

  for (int i = 0; i < n; i++)
  {
    int r = i + (rand() % (52 - i));
    swap(deck[i], deck[r]);
  }
}

void printCard(CARD *input)
{
  printf("[%c %d]\n", input->suit, input->num);
}

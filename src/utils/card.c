#include "card.h"

// void build_deck(CARD *deck[])
// {
//   int i, j, k = 0;
//
//   char suits[4] = "dchs";
//
//   for (i = 0; i < 4; i++)
//   {
//     for (j = 0; j < 13; j++)
//     {
//       CARD *card = malloc(sizeof(CARD));
//       card->suit = suits[i];
//       card->num = j + 1;
//       deck[k++] = card;
//     }
//   }
// }
//
// void swap(CARD *a, CARD *b)
// {
//   CARD temp = *a;
//   *a = *b;
//   *b = temp;
// }
//
// void shuffle(CARD *deck[], int n)
// {
//   srand(time(0));
//
//   for (int i = 0; i < n; i++)
//   {
//     int r = i + (rand() % (52 - i));
//     swap(deck[i], deck[r]);
//   }
// }

void getCards(struct card deck[]) {
  char * suits = "dchs";
  int i;
  srand(time(0));

  for (i = 0; i < 13; i++) {
    int list[4][13] = {0};
    int suit = rand() % 4;
    int num = rand() % 13;
    if (list[suit][num] == 0) {
      list[suit][num] = 1;
      deck[i].suit = suits[suit];
      deck[i].num = num+1;
    }
    else {
      i--;
    }
  }
}

void printCard(CARD input)
{
  setlocale(LC_CTYPE, "");
  wchar_t suit;
  if (input.suit == 'd') {
    suit = 0x2666;
  }
  if (input.suit == 's') {
    suit = 0x2660;
  }
  if (input.suit == 'h') {
    suit = 0x2665;
  }
  if (input.suit == 'c') {
    suit = 0x2663;
  }
  printf("[%lc %d]\n", suit, input.num);
}

//royal flush -> 10
//straight flush
//four of a kind
//full house
//flush
//straight
//triple
//two pairs
//pair
//high card -> 1

int getValue(CARD * hand) {
  return 0;
}

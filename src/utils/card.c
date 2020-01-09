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

void getCards(DECK * deck) {
  char * suits = "dchs";
  int i;
  srand(time(0));
  int list[4][13] = {0};
  for (i = 0; i < 8; i++) {
    int suit = rand() % 4;
    int num = rand() % 13;
    if (list[suit][num] == 0) {
      list[suit][num] = 1;
      //printf("%d, %d\n", i/2, i%2);
      deck->hand[i / 2].hand[i % 2].suit = suits[suit];
      deck->hand[i / 2].hand[i % 2].num = num+1;
      //printCard(deck->hand[i/2].hand[i%2]);
    }
    else {
      i--;
    }
  }
  for (i = 0; i < 5; i++) {
    int suit = rand() % 4;
    int num = rand() % 13;
    if (list[suit][num] == 0) {
      list[suit][num] = 1;
      deck->house[i].suit = suits[suit];
      deck->house[i].num = num+1;
      //printCard(deck->house[i]);
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

void printDeck(DECK * deck) {
  //printf("JEFF SUCKS\n");
  printCard(deck->hand[0].hand[0]);
  printCard(deck->hand[0].hand[1]);
  printCard(deck->hand[1].hand[0]);
  printCard(deck->hand[1].hand[1]);
  printCard(deck->hand[2].hand[0]);
  printCard(deck->hand[2].hand[1]);
  printCard(deck->hand[3].hand[0]);
  printCard(deck->hand[3].hand[1]);
  printCard(deck->house[0]);
  printCard(deck->house[1]);
  printCard(deck->house[2]);
  printCard(deck->house[3]);
  printCard(deck->house[4]);
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

// int getValue(DECK deck, int player, int count) {
//   struct card card1 = deck.hand[player].hand[0];
//   if (count == 0) {
//     if deck
//   }
// }

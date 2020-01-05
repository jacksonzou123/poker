#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "card.h"

void getCards(struct card deck[]) {
  char * suits = "dchs";
  srand(time(0));

  int i;
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

void printCard(struct card input) {
  printf("%c%d\n", input.suit, input.num);
}

int main() {
  struct card deck[13];
  getCards(deck);
  int i = 0;
  for (i = 0; i < 13; i++) {
    printCard(deck[i]);
  }
  return 0;
}

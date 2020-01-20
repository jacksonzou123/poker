#include "logic.h"

int best_hand(BOARD *board, HAND *hand) {
  int highest = HIGHCARD;

  int temp = checkmultiple(board, hand);
  if (temp > highest) {
    highest = temp;
  }

  return highest;
}

int checkmultiple(BOARD *board, HAND *hand) {
  int counter[13] = {0};

  int i;
  int two = 0;
  int three = 0;

  counter[board->a->num-1]++;

  //count doubles, triples, quads
  for (i = 0; i < 13; i++) {
    if (counter[i] == 2) {
      two++;
    }
    if (counter[i] == 3) {
      three++;
    }
    if (counter[i] == 4) {
      return FOUR_OF_A_KIND;
    }
  }

  if (three == 1) {
    if (two > 0) {
      return FULL_HOUSE;
    }
    return THREE_OF_A_KIND;
  }
  if (two >= 2) {
    //two pair
    return TWO_PAIRS;
  }
  if (two == 1) {
    //pair
    return PAIRS;
  }
  //nothing
  return HIGHCARD;
}

int checkStraightFlush(BOARD * board, HAND * hand) {
  int scheck[13] = {0};
  int fcheck[4] = {0}; //d-0 c-1 h-2 s-3

  int straight = 0;
  int flush = 0;

  return HIGHCARD;
}

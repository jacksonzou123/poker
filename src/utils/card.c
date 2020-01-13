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
  printf("Player 0 Cards:\n");
  printCard(deck->hand[0].hand[0]);
  printCard(deck->hand[0].hand[1]);
  printf("Player 1 Cards:\n");
  printCard(deck->hand[1].hand[0]);
  printCard(deck->hand[1].hand[1]);
  printf("Player 2 Cards:\n");
  printCard(deck->hand[2].hand[0]);
  printCard(deck->hand[2].hand[1]);
  printf("Player 3 Cards:\n");
  printCard(deck->hand[3].hand[0]);
  printCard(deck->hand[3].hand[1]);
  printf("Field\n");
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


//count is the number of cards in the house being used
char * getValue(DECK * deck, int player, int count) {
  int value = handValue(deck, player, count);
  if (value == 1) {
    return "high card";
  }
  if (value == 2) {
    return "pair";
  }
  if (value == 3) {
    return "two pair";
  }
  if (value == 4) {
    return "triple";
  }
  if (value == 5) {
    return "straight";
  }
  if (value == 6) {
    return "flush";
  }
  if (value == 7) {
    return "full house";
  }
  if (value == 8) {
    return "four of a kind";
  }
  if (value == 9) {
    return "straight flush";
  }
  if (value == 10) {
    return "royal flush";
  }
  return "dab";
}

int handValue(DECK * deck, int player, int count) {
  CARD hand[2 + count];
  hand[0] = deck->hand[player].hand[0];
  hand[1] = deck->hand[player].hand[1];

  int i;
  for (i = 0; i < count; i++) {
    hand[2+i] = deck->house[i];
  }

  // for (i = 0; i < count+2; i++) {
  //   printCard(hand[i]);
  // }
  if (count <= 2) {
    return countMultiple(hand, count+2);
  }
  if (count >= 3) {
    int highest = 1;
    int check = countMultiple(hand, count+2);
    if (check > highest) {
      highest = check;
    }
    check = checkStraightFlush(hand, count+2);
    if (check > highest) {
      highest = check;
    }
    return highest;
  }
  return 0;
}

int countMultiple(CARD hand[], int numCards) {
  int counter[13] = {0};
  int i;

  int two = 0;
  int three = 0;

  for (i = 0; i < numCards; i++) {
    counter[hand[i].num-1]++;
  }

  //count doubles, triples, quads
  for (i = 0; i < 13; i++) {
    if (counter[i] == 2) {
      two++;
    }
    if (counter[i] == 3) {
      three++;
    }
    if (counter[i] == 4) {
      return 8;
    }
  }

  if (three == 1) {
    if (two > 0) {
      //full house
      return 7;
    }
    //triples
    return 4;
  }
  if (two >= 2) {
    //two pair
    return 3;
  }
  if (two == 1) {
    //pair
    return 2;
  }
  //nothing
  return 1;
}

int checkStraightFlush(CARD hand[], int numCards) {
  int scheck[13] = {0};
  int fcheck[4] = {0}; //d-0 c-1 h-2 s-3

  int straight = 0;
  int flush = 0;

  int i;
  for (i = 0; i < numCards; i++) {
    scheck[hand[i].num-1]++;
    if (hand[i].suit == 'd') {
      fcheck[0]++;
    }
    if (hand[i].suit == 'c') {
      fcheck[1]++;
    }
    if (hand[i].suit == 'h') {
      fcheck[2]++;
    }
    if (hand[i].suit == 's') {
      fcheck[3]++;
    }
  }

  // for (i = 0; i < 4; i++) {
  //   printf("%d\n", fcheck[i]);
  // }

  //look for flushes
  for (i = 0; i < 4; i++) {
    if (fcheck[i] >= 5) {
      flush = 1;
    }
  }

  int counter = 0;
  int highest = 0;
  for (i = 0; i <= 13; i++) {
    if (i == 13) {
      if (scheck[0]) {
        if (counter >= 4) {
          straight = 1;
          highest = 1;
        }
      }
    }
    else {
      if (scheck[i]) {
        counter++;
      }
      else {
        counter = 0;
      }
      if (counter >= 5) {
        highest = i-1;
        straight = 1;
      }
    }
  }

  if (flush) {
    return 6;
  }
  if (straight) {
    return 5;
  }
  return 1;
  //look for straights

}

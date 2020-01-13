#ifndef CARD_H
#define CARD_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

typedef struct card
{
  char suit;
  int num;
} CARD;

typedef struct hand
{
  char player[256];
  CARD hand[2];
} HAND;

typedef struct deck
{
  HAND hand[4];
  CARD house[5];
} DECK;

typedef int boolean;
#define TRUE 1;
#define FALSE 0;

// void build_deck(CARD **);
// void swap(CARD *, CARD *);
// void shuffle(CARD **, int);
// void printCard(CARD *);
//void getCards(char *deck[]);
void getCards(DECK * deck);
void printCard(CARD input);
void printDeck(DECK * deck);
char * getValue(DECK * deck, int player, int count);
int handValue(DECK * deck, int player, int count);

int countMultiple(CARD hand[], int numCards);
int checkStraightFlush(CARD hand[], int numCards);
#endif

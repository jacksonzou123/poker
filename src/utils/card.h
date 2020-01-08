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
};

typedef struct deck
{
  CARD deck[13];
} DECK;

typedef int boolean;
#define TRUE 1;
#define FALSE 0;

// void build_deck(CARD **);
// void swap(CARD *, CARD *);
// void shuffle(CARD **, int);
// void printCard(CARD *);
//void getCards(char *deck[]);
void getCards(CARD deck[]);
void printCard(CARD input);

#endif

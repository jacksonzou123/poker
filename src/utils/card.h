#ifndef CARD_H
#define CARD_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct card
{
  char suit;
  int num;
} CARD;

void build_deck(CARD **);
void swap(CARD *, CARD *);
void shuffle(CARD **, int);
void printCard(CARD *);

#endif
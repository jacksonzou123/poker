#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include <time.h>
#include <string.h>

#define FULL_DECK_SIZE 52
#define TWO_PLAYER_DECK_SIZE 9
#define THREE_PLAYER_DECK_SIZE 11
#define FOUR_PLAYER_DECK_SIZE 13

/*
 * Card Type
 * 
 * @suit: Diamond, Club, Heart, or Spade
 * @num: From 1 to 13 Where 1 is Ace and 13 is King
 */
typedef struct card
{
  char suit[10];
  int num;
} CARD;

// Card Utility Functions
char *num_to_suit(int card);
int card_to_num(CARD *card);
void print_card(CARD *input);
int compare_card(CARD *, CARD *);
char *stringify_cards(CARD **deck, int n);

/*
 * Return Card Pointer Array
 */
CARD **get_cards();

#endif
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define FULL_DECK_SIZE 52
#define TWO_PLAYER_DECK_SIZE 9
#define THREE_PLAYER_DECK_SIZE 11
#define FOUR_PLAYER_DECK_SIZE 13

/*
 * Card Interface
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
void print_card(CARD *input);

/*
 * @param player_num
 * @param num_cards
 * 
 * Return Card Pointer Array
 */
CARD **get_cards(int, int);

/*
 * Hand Interface
 * 
 * @player: Player's Name
 * @card_a: Player's First Card
 * @card_b: Player's Second Card
 */
typedef struct hand
{
  char player[100];
  CARD *card_a, *card_b;
} HAND;

HAND *make_hand(char *, CARD *, CARD *);
HAND **dist_cards(char **, int, CARD **, int);

/*
 * Board Interface
 * 
 * Five Cards of the House
 * 
 * @a
 * @b
 * @c
 * @d
 * @e
 */
typedef struct board
{
  CARD *a, *b, *c, *d, *e;
} BOARD;

BOARD *fill_board(CARD **);

#endif
#ifndef LOGIC_H
#define LOGIC_H

#include "util.h"

#define HIGHCARD 1
#define PAIRS 2
#define TWO_PAIRS 3
#define THREE_OF_A_KIND 4
#define STRAIGHT 5
#define FLUSH 6
#define FULL_HOUSE 7
#define FOUR_OF_A_KIND 8
#define STRAIGHT_FLUSH 9
#define ROYAL_FLUSH 10

/*
 * Evaluate a player's hand,
 * and return the value of the
 * player's best hand.
 */
int best_hand(BOARD *, HAND *);

/*
 * Should only be called if the
 * player's hands have no combos.
 * 
 * Evaluate all player's hands,
 * and return the player's name
 * with the highest card.
 */
char *compare_high_card(HAND **);

/*
 * Check for the following combos.
 */

int is_pair(BOARD *, HAND *);
int is_two_pairs(BOARD *, HAND *);
int is_three_of_a_kind(BOARD *, HAND *);
int is_straight(BOARD *, HAND *);
int is_flush(BOARD *, HAND *);
int is_full_house(BOARD *, HAND *);
int is_four_of_a_kind(BOARD *, HAND *);
int is_straight_flush(BOARD *, HAND *);
int is_royal_flush(BOARD *, HAND *);

#endif
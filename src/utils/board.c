#include "util.h"

/*
 * Assume five cards remain.
 */
BOARD *fill_board(CARD **cards)
{
  int i;
  BOARD *board = malloc(sizeof(void *));

  board->a = cards[0];
  board->b = cards[1];
  board->c = cards[2];
  board->d = cards[3];
  board->e = cards[4];

  return board;
}
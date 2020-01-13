#include "net/tcp.h"
#include "utils/card.h"

int main(int argc, char const *argv[])
{
  DECK * deck = malloc(sizeof(DECK));
  getCards(deck);
  printDeck(deck);

  printf("Player 0: %s\n", getValue(deck, 0, 5));
  printf("Player 1: %s\n", getValue(deck, 1, 5));
  printf("Player 2: %s\n", getValue(deck, 2, 5));
  printf("Player 3: %s\n", getValue(deck, 3, 5));
  return 0;
}

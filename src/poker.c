#include "net/tcp.h"
#include "utils/card.h"

int main(int argc, char const *argv[])
{
  DECK * deck = malloc(sizeof(DECK));
  getCards(deck);
  printDeck(deck);
  return 0;
}

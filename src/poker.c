#include "net/udp.h"
#include "utils/card.h"

int main(int argc, char const *argv[])
{
  CARD *deck[52];
  build_deck(deck);
  shuffle(deck, 52);
  int i = 0;
  for (i = 0; i < 52; i++)
  {
    printCard(deck[i]);
  }
  return 0;
}

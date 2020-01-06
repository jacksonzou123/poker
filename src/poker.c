#include "net/udp.h"
#include "utils/card.h"

int main(int argc, char const *argv[])
{
  CARD deck[13];
  getCards(deck);
  int i = 0;
  for (i = 0; i < 52; i++)
  {
    printCard(deck[i]);
  }
  return 0;
}

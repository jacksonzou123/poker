#include "net/net.h"
#include "utils/card.h"
#include "utils/game.h"

// int main(int argc, char const *argv[])
// {
//   int numPlayers = 4;
//   PLAYER players[numPlayers];
//   initPlayers(players, numPlayers);

//   // printf("Player 0: %s\n", getValue(deck, 0, 5));
//   // printf("Player 1: %s\n", getValue(deck, 1, 5));
//   // printf("Player 2: %s\n", getValue(deck, 2, 5));
//   // printf("Player 3: %s\n", getValue(deck, 3, 5));
//   return 0;
// }

// Testing Server
int main(int argc, char const *argv[])
{
  serve("8000");
  return 0;
}

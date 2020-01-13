#include "card.h"
#include <string.h>

typedef struct player
{
  char name[256];
  int total;
  int current;
} PLAYER;

void initPlayers(PLAYER players[], int num);

void turn(PLAYER players[], int num);

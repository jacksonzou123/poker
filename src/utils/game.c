#include "game.h"

void initPlayers(PLAYER players[], int num) {
  int i;
  for (i = 0; i < num; i++) {
    players[i].total = 1000;
    players[i].current = 0;
    strcpy(players[i].name, "dabdab");
  }
}

void turn(PLAYER players[], int num) {
  DECK * deck = malloc(sizeof(DECK)); //initialize deck
  getCards(deck);
  //printDeck(deck);
  int i;

  int pIN[num];
  for (i = 0; i < num; i++) {
    pIN[i] = 1; //this array will be used to check whether the player is still in the hand
  }

  int totalpot = 0;
  int current = 0;

  int cardsShown = 0;

  while (cardsShown <= 5) {
    for (i = 0; i < num; i++) {
      if (!sizeof(players[i]) && pIN[i]) { //if players[i] is NULL, then they're out of the game
        char * move = "yols";       //get player move and amount
        if (*(move) == 'c') {
          continue; //check
        }
        if (*(move) == 'f') {
          pIN[i] = 0; //fold
        }
        if (*(move) == 'r') {
          //raise
          //update current
        }
        if (*(move) == 'm') {
          //call or match
          //can only do this if player[i].current < current
        }
      }
    }

    int check = 1;

    for (i = 0; i < num; i++) {
      if(!sizeof(players[i]) && pIN[i]) {
        if (players[i].current != current) {
          check = 0;
        }
      }
    }

    if (check) {
      cardsShown++;
    }
  }


}

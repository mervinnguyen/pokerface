/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_gamelogic.c: Unit test for gamelogic	                 */
/*********************************************************************/

#include "gamelogic.h"

int main()
{
    struct Deck *deck;
    struct Game *game;

    int numPlayers = 4;
    int smallBlind = 10;
    int bigBlind = 20;
    int startingChips = 1000;

    makeDeck(&deck);

    printDeck(&deck);

    shuffleDeck(&deck);

    printDeck(&deck);

    dealCards(&game);


}



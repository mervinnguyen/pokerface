/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_gamelogic.c: Unit test for gamelogic	                 */
/*********************************************************************/

#include "gamelogic.h"

// made a function to itterate through the deck and print

void printcurrentDeck(const Deck *deck) {
    for (int i = 0; i < NUM_CARDS; ++i) {
        printf("Card %d: Suit %d, Rank %d\n", i+1, deck->cards[i].suit, deck->cards[i].rank);
    }
}

int main()
{
    Deck deck;
    Game game;
    Player player;

    int numPlayers = 4;
    int smallBlind = 10;
    int bigBlind = 20;
    int startingChips = 1000;

    //These are the deck functions
    makeDeck(&deck);
    printf("Printing deck: \n");
    printcurrentDeck(&deck);
    printf("These are the cards printed");

    //I lowkey dont know how to test this one through print statements 
    printDeck(&deck);
    displayCommunityCards(&deck);

    shuffleDeck(&deck);
    printf("Printing deck: \n");
    printcurrentDeck(&deck);
    printf("These are the cards printed");

    dealCards(&game);
    
    initGame(&game, numPlayers);
    startGame(&game);

    displayPlayerCards(&player);




}



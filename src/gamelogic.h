<<<<<<< HEAD
#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <stdlib.h>
#include <stdbool.h>

typedef enum{
=======
/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                     	 */
/* gamelogic.h: gamelogic header file								 */
/*********************************************************************/

#ifndef POKER_H
#define POKER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52
#define CARDS_PER_PLAYER 2
#define NUM_RANKS 13

typedef enum {
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07
    SPADES = 0,
    CLUBS = 1,
    DIAMONDS = 2,
    HEARTS = 3
<<<<<<< HEAD
}SUIT;

typedef enum{
=======
} SUIT;

typedef enum {
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,
    QUEEN = 12,
    KING = 13,
    ACE = 14
<<<<<<< HEAD
}RANK;
=======
} RANK;
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07

typedef enum {
    PREFLOP = 0,
    FLOP = 1,
    TURN = 2,
    RIVER = 3
<<<<<<< HEAD
}ROUND;
=======
} ROUND;
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07

typedef enum {
    SMALL_BLIND = 0,
    BIG_BLIND = 1,
    REGULAR = 2
<<<<<<< HEAD
}BLIND;

typedef struct {
	SUIT suit;
	RANK rank;
}Card;

typedef struct {
	struct Card cards[NUM_CARDS];
	int top;
}Deck;
=======
} BLIND;

typedef struct {
    SUIT suit;
    RANK rank;
} Card;

typedef struct {
    Card cards[5];
} Hand;

typedef struct {
    Card cards[NUM_CARDS];
    int top;
} Deck;
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07

typedef enum {
    FOLD = 0,
    CHECK = 1,
    CALL = 2,
    RAISE = 3
<<<<<<< HEAD
}Moves;
=======
} Moves;
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07

typedef struct {
    int chips;
    int bet;
    int raise;
    Card card1;
    Card card2;
    Moves move;
<<<<<<< HEAD
}Player;

//create a struct for the state of the game
=======
} Player;

>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07
typedef struct {
    int pot;
    ROUND round;
    int currentCall;
    int numPlayers;
    int currentPlayer;
    int numGames;
    int dealer;
    int smallBlind;
    int bigBlind;
    int raise;
    int maxBet;
    int minBet;
    int maxRaise;
    int minRaise;
    int numFolded;
    int numCalled;
    int numRaised;
    int numChecked;
    int numAllIn;
    Player players[7];
    Deck shuffleDeck;
    Deck communityCards;
<<<<<<< HEAD
}Game;
=======
} Game;

extern const char *suits[];
extern const char *ranks[];

void makeDeck(Deck *deck);
void shuffleDeck(Deck *deck);
void dealCards(Game *game);
int CheckPlayer(Game *game, int player);
int CheckRoyalFlush(Game *game, int player);
int CheckStraightFlush(Game *game, int player);
int CheckFourOfAKind(Game *game, int player);
int CheckFullHouse(Game *game, int player);
int CheckFlush(Game *game, int player);
int CheckStraight(Game *game, int player);
int CheckThreeOfAKind(Game *game, int player);
int CheckTwoPair(Game *game, int player);
int CheckPair(Game *game, int player);
int CheckHighCard(Game *game, int player);
Deck* SortbyRank(Deck *D);
Deck* SortbySuit(Deck *D);
void initGame(Game *game, int numPlayers);
void playerAction(Game *game, int playerIndex);
void startGame(Game *game);
void displayPlayerCards(Player *player);
void displayCommunityCards(Deck *communityCards);



#endif // POKER_H
>>>>>>> f2339945f9da2addcab57d825a66a2c3ddd39d07


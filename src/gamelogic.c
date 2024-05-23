#include <stdio.h>
#include <stdlib.h>
#include <time.h>

<<<<<<< HEAD
typedef struct {
    int rank;
    int suit;
}Card;

typedef struct {
    Card card hand[5];
}Hand;

typedef struct {
    struct Card cards[NUM_CARDS];
    int top;
}Deck;

typedef struct {
    sttuct Card hand[CARDS_PER_PLAYER];
}Player;

int CheckRoyalFlush(){

}

=======
#define NUM_CARDS 52
#define CARDS_PER_PLAYER 2

typedef enum{
    SPADES = 0,
    CLUBS = 1,
    DIAMONDS = 2,
    HEARTS = 3
}SUIT;

//Assign values to face cards
typedef enum{
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
}RANK;

typedef struct {
	SUIT suit;
	RANK rank;
}Card;

typedef struct {
	struct Card hand[5];
}Hand;

typedef struct {
	struct Card cards[NUM_CARDS];
	int top;
}Deck;

typedef struct {
	struct Card hand[CARDS_PER_PLAYER];
}Player;


void makeDeck(Card *deck) 
{
    int count = 0;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 0; rank < 13; rank++)
        {
            print("Hello World");
        }
    }
}

int CheckPlayer(){
    int priority;
    if(CheckRoyalFlush() == 1){
        priority = 10;
    }
    else if(CheckStraightFlush() == 1){
        priority = 9;
    }
    else if(CheckFourOfAKind() == 1){
        priority = 8;
    }
    else if(CheckFullHouse() == 1){
        priority = 7;
    }
    else if(CheckFlush() == 1){
        priority = 6;
    }
    else if(CheckStraight() == 1){
        priority = 5;
    }
    else if(CheckThreeOfAKind() == 1){
        priority = 4;
    }
    else if(CheckTwoPair() == 1){
        priority = 3;
    }
    else if(CheckPair() == 1){
        priority = 2;
    }
    else{
        priority = 1;
    }
}

int CheckRoyalFlush(){
    
}


>>>>>>> afdb0fd2490946ec64216adcc465c192cc8cd540
int CheckStraightFlush(){

}

int CheckFourOfAKind(){

}

int CheckFullHouse(){

}

int CheckFlush(){

}

int CheckStraight(){

}

int CheckThreeOfAKind(){

}

int CheckTwoPair(){

}

int CheckPair(){

}

int CheckHighCard(){

}

int main(){
    return 0;
}	

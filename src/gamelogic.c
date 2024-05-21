#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

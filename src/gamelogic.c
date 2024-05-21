#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int rank;
    int suit;
} Card;

const char suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const charranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

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

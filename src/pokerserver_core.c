/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* pokersever.c: Main file for the sever			                 */
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

#include "pokerserver_core.h"

/*
#define MAX_MESSAGE_LEN 255
#define PORT_NUMBER_LOWER_BOUND 1024
#define CONCURRENT_CLIENT_NUM 5
#define MAX_CARDS_PER_CLIENT 52
*/

char clientCardsMap[CONCURRENT_CLIENT_NUM][MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1];

int getPortNum(int argc, char *const *argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong params. Usage: %s port\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int portNum = atoi(argv[1]);
    if (portNum <= PORT_NUMBER_LOWER_BOUND) {
        fprintf(stderr, "[%s] invalid port number %d, should be greater than %d\n", argv[0], portNum, PORT_NUMBER_LOWER_BOUND);
        exit(EXIT_FAILURE);
    }
    return portNum;
}

int strlen_without_null(const char *str) {
    int length = 0;
    while (*str != '\0' && *str != '\n') {
        ++length;
        ++str;

    }
    return length;
}

char** initializeCards() {
    char** cards = (char**)malloc(MAX_CARDS_PER_CLIENT * sizeof(char*));
    if (cards == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    /* shapes */
    char* shapes[] = {"hearts", "diamonds", "clubs", "spades"};
    /* marks */
    char* marks[] = {"ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "joker", "queen", "king"};
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            char* card = (char*)malloc((strlen(marks[j]) + strlen(shapes[i]) + 2) * sizeof(char));
            if (card == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(card, marks[j]);
            strcat(card, "_of_");
            strcat(card, shapes[i]);
            cards[index++] = card;
        }
    }
    return cards;
}


void shuffleCards(char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1], int numCards) {
    srand(time(NULL)); // Seed the random number generator
    char temp[MAX_MESSAGE_LEN + 1];
    for (int i = numCards - 1; i > 0; i--) {
        /* Generate a random index between 0 and i (inclusive) */
        int j = rand() % (i + 1);
        while (i == j) {
            j = rand() % (i + 1);
        }

        /* Swap cards[i] and cards[j] */
        /* fprintf(stderr, "cards[%d]: %s, cards[%d]: %s\n", i, cards[i], j, cards[j]); */
        strcpy(temp, cards[i]);
        strcpy(cards[i], cards[j]);
        strcpy(cards[j], temp);
    }
}

int getFirstCardsIndex(char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1], int numCards) {
    for (int i = numCards - 1; i > 0; --i) {
        /* fprintf(stderr, "cards[%d]: %s\n", i, cards[i]); */
        if (strcmp(cards[i], "SENT") != 0) {
            return i;
        }
    }
    return -1;
}

time_t currentTime;


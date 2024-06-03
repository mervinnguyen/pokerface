#ifndef POKERSERVER_CORE_H
#define POKERSERVER_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX_MESSAGE_LEN 255
#define PORT_NUMBER_LOWER_BOUND 1024
#define CONCURRENT_CLIENT_NUM 5
#define MAX_CARDS_PER_CLIENT 52

char clientCardsMap[CONCURRENT_CLIENT_NUM][MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1];

int getPortNum(int argc, char *const *argv);

int strlen_without_null(const char *str);

char** initializeCards();

void shuffleCards(char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1], int numCards);

int getFirstCardsIndex(char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1], int numCards);

time_t currentTime;

#endif

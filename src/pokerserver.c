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

#define MAX_MESSAGE_LEN 255
#define PORT_NUMBER_LOWER_BOUND 1024
#define CONCURRENT_CLIENT_NUM 5
#define MAX_CARDS_PER_CLIENT 52

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

    // shapes
    char* shapes[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    // marks
    char* marks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int index = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 13; ++j) {
            char* card = (char*)malloc((strlen(marks[j]) + strlen(shapes[i]) + 2) * sizeof(char));
            if (card == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            strcpy(card, marks[j]);
            strcat(card, "-");
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
        // Generate a random index between 0 and i (inclusive)
        int j = rand() % (i + 1);
        while (i == j) {
            j = rand() % (i + 1);
        }

        // Swap cards[i] and cards[j]
        // fprintf(stderr, "cards[%d]: %s, cards[%d]: %s\n", i, cards[i], j, cards[j]);
        strcpy(temp, cards[i]);
        strcpy(cards[i], cards[j]);
        strcpy(cards[j], temp);
    }
}

int getFirstCardsIndex(char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1], int numCards) {
    for (int i = numCards - 1; i > 0; --i) {
        // fprintf(stderr, "cards[%d]: %s\n", i, cards[i]);
        if (strcmp(cards[i], "SENT") != 0) {
            return i;
        }
    }
    return -1;
}

time_t currentTime;

int main(int argc, char *argv[]) {
    int serverSocket, dataSocket, portNum;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t clientLen;
    int bytesReceived, bytesSent;
    char receiveBuffer[MAX_MESSAGE_LEN + 1];
    char sendBuffer[MAX_MESSAGE_LEN + 20];

    portNum = getPortNum(argc, argv);

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(portNum);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        fprintf(stderr, "[%s] %s\n", argv[0], "failed to create server socket");
        exit(EXIT_FAILURE);
    }

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        fprintf(stderr, "[%s] %s\n", argv[0], "failed to bind to server socket");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, CONCURRENT_CLIENT_NUM) < 0) {
        fprintf(stderr, "[%s] %s\n", argv[0], "listening on socket failed");
        exit(EXIT_FAILURE);
    }

    printf("[%s] start listening on %d...\n", argv[0], portNum);

    do {
        clientLen = sizeof(clientAddress);
        dataSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientLen);

        if (dataSocket < 0) {
            fprintf(stderr, "[%s] %s\n", argv[0], "failed at data socket creation");
            exit(EXIT_FAILURE);
        }
        printf("[%s] got a connection from client.\n", argv[0]);
        if (clientCardsMap[dataSocket][0][0] == '\0') {
            char **cards = initializeCards();
            for (int i = 0; i < MAX_CARDS_PER_CLIENT; ++i) {
                strcpy(clientCardsMap[dataSocket][i], cards[i]);
                free(cards[i]);
            }
            free(cards);
            shuffleCards(clientCardsMap[dataSocket], MAX_CARDS_PER_CLIENT);
        }
        do {
            bytesReceived = read(dataSocket, receiveBuffer, sizeof(receiveBuffer) - 1);
            if (bytesReceived < 0) {
                fprintf(stderr, "[%s] %s\n", argv[0], "reading from data socket failed");
                exit(EXIT_FAILURE);
            }
            receiveBuffer[bytesReceived] = '\0';
            printf("[%s] message Received: %s\n %d %d", argv[0], receiveBuffer, strlen_without_null(receiveBuffer), strncmp(receiveBuffer, "current time", strlen_without_null(receiveBuffer)));

            if (strncmp(receiveBuffer, "bye", strlen_without_null(receiveBuffer)) == 0) {
                strncpy(sendBuffer, "server bye", sizeof(sendBuffer));
            } else if (strncmp(receiveBuffer, "shutdown", strlen_without_null(receiveBuffer)) == 0) {
                strncpy(sendBuffer, "server shutdown", sizeof(sendBuffer));
            } else if (strncmp(receiveBuffer, "current time", strlen_without_null(receiveBuffer)) == 0) {
                time(&currentTime);
                struct tm *timeinfo = localtime(&currentTime);
                strftime(sendBuffer, 20, "%Y-%m-%d %H:%M:%S", timeinfo);
            } else if (strncmp(receiveBuffer, "give me cards", strlen_without_null(receiveBuffer)) == 0) {
                char* sendOutCards = (char*)malloc(100 * sizeof(char));
                int firstIndex = getFirstCardsIndex(clientCardsMap[dataSocket], MAX_CARDS_PER_CLIENT);
                if (firstIndex == -1) {
                    free(sendOutCards);
                    strncpy(sendBuffer, "no cards available", sizeof(sendBuffer));
                }
                strcpy(sendOutCards, clientCardsMap[dataSocket][firstIndex]);
                strcpy(clientCardsMap[dataSocket][firstIndex], "SENT");

                int secondIndex = getFirstCardsIndex(clientCardsMap[dataSocket], MAX_CARDS_PER_CLIENT);
                if (secondIndex == -1) {
                    free(sendOutCards);
                    strncpy(sendBuffer, "no cards available", sizeof(sendBuffer));
                }
                if (firstIndex != -1 && secondIndex != -1) {

                    strcat(sendOutCards, ",");
                    strcat(sendOutCards, clientCardsMap[dataSocket][secondIndex]);
                    strcpy(clientCardsMap[dataSocket][secondIndex], "SENT");
                    strncpy(sendBuffer, sendOutCards, sizeof(sendBuffer));
                    free(sendOutCards);
                }
            } else {
                snprintf(sendBuffer, sizeof(sendBuffer), "server received %s", receiveBuffer);
            }

            printf("[%s] response to client: %s.\n", argv[0], sendBuffer);
            bytesSent = write(dataSocket, sendBuffer, strlen(sendBuffer));
            if (bytesSent < 0) {
                fprintf(stderr, "[%s] %s\n", argv[0], "failed at writing to data socket");
                exit(EXIT_FAILURE);
            }
        } while (strcmp(receiveBuffer, "bye") != 0 && strcmp(receiveBuffer, "shutdown") != 0);

        printf("[%s] going to disconnect with current client.\n", argv[0]);
        close(dataSocket);

    } while (strcmp(receiveBuffer, "shutdown") != 0);

    printf("[%s] Shutting down.\n", argv[0]);
    close(serverSocket);
    return 0;
}
/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* pokerclient.c: Main file for the client			                 */
/*********************************************************************/

#include "pokerclient_core.h"

int main(int argc, char *argv[])
{
    
	// GTK Variables
	GtkWidget *window = NULL;	// Main window
	
	// Array used to print the dealer cards on the poker table in the GUI. Note: Inputing incorrect string notation will result in a card shadow to be created instead on the GUI. Notation: RANK_of_SUIT; ex: ace_of_spades
	char dealt_cards[5][STRING_BUFFER] = {"ace_of_spades", "8_of_hearts", "jack_of_diamonds", "4_of_clubs","10_of_spades"};
	printf("Dealer Cards:\nCard 1: %s, Card 2: %s, Card 3: %s, Card 4: %s, Card 5: %s\n", dealt_cards[0], dealt_cards[1], dealt_cards[2], dealt_cards[3], dealt_cards[4]);

	// Testing
	char *testing = "Card 1: king_of_diamonds, Card 2: queen_of_diamonds";
	char card_1[100] = "back_card";
	char card_2[100] = "back_card";
	char card_3[100] = "back_card";
	char card_4[100] = "back_card";
	char card_5[100] = "back_card";
	// Copying strings
	printf("inital string: %s\n", testing);
	// Use sscanf to extract substrings
    if (sscanf(testing, "Card 1: %100[^,], Card 2: %100[^,]", card_1, card_2) == 2)
	{
        printf("Card 1: %s\n", card_1);
        printf("Card 2: %s\n", card_2);
		strncpy(dealt_cards[0], card_1, 100);
		strncpy(dealt_cards[1], card_2, 100);
		strncpy(dealt_cards[2], card_3, 100);
		strncpy(dealt_cards[3], card_4, 100);
		strncpy(dealt_cards[4], card_5, 100);
    }
	
	// Creates a GUI for client
	window = CreateClientWindow(&argc, &argv, dealt_cards);
	// Checks that a window pointer has been returned
	if (!window)
    {
		// Prints error to standard error stream
		fprintf(stderr, "GTKWidget ointer to window has not been returned.\n");
        // Error Code #1
		return 1;
    }
	
	char *hostName = argv[1];
    int portNum = 0;
    getPortNum(argc, argv, &portNum);

    struct hostent *host = gethostbyname(hostName);
    if (host == NULL) {
        fprintf(stderr, "[%s] host name '%s' is not found\n", argv[0], hostName);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNum);
    memcpy(&serverAddr.sin_addr.s_addr, host->h_addr_list[0], host->h_length);

    int socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0) {
        fprintf(stderr, "[%s] failed at socket creation\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (connect(socketFD, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        fprintf(stderr, "[%s] connecting to host failed\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pthread_t listenerThread; // Added
    int *socketPtr = malloc(sizeof(int)); // Added
    if (socketPtr == NULL) { // Added
        fprintf(stderr, "Memory allocation failed.\n"); // Added
        close(socketFD); // Added
        exit(EXIT_FAILURE); // Added
    }
    *socketPtr = socketFD; // Added
    if (pthread_create(&listenerThread, NULL, listenForMessages, socketPtr) != 0) { // Added
        fprintf(stderr, "Listener thread creation failed.\n"); // Added
        close(socketFD); // Added
        free(socketPtr); // Added
        exit(EXIT_FAILURE); // Added
    }

    char sendBuffer[MAX_MESSAGE_LEN + 1];
    char recvBuffer[MAX_MESSAGE_LEN + 1];

    do {
        printf("[%s] enter a message to send to the host,\n", argv[0]);
        printf("         or 'bye' to quit this client,\n");
        printf("         or 'shutdown' to quit both host and client,\n");
        printf("         or 'current time' to get the current server time,\n");
        printf("         or 'give me cards' to get 2 random cards.\n");
        printf("message: ");
        fgets(sendBuffer, sizeof(sendBuffer), stdin);
        sendBuffer[strlen(sendBuffer) - 1] = '\0';
        int Length = strlen(sendBuffer);

        if (Length) {
            printf("[%s] Sending message '%s'...\n", argv[0], sendBuffer);
            int BytesSent = write(socketFD, sendBuffer, Length);
            if (BytesSent < 0) {
                fprintf(stderr, "[%s] writing to socket failed\n", argv[0]);
                close(socketFD); // Added
                exit(EXIT_FAILURE);
            }

            int BytesReceived = read(socketFD, recvBuffer, sizeof(recvBuffer) - 1);
            if (BytesReceived < 0) {
                fprintf(stderr, "[%s] reading from socket failed\n", argv[0]);
                close(socketFD); // Added
                exit(EXIT_FAILURE);
            }
            recvBuffer[BytesReceived] = '\0';
            printf("[%s] Received response: %s\n", argv[0], recvBuffer);
        }
    } while (strcmp("server bye", recvBuffer) != 0 && strcmp("server shutdown", recvBuffer) != 0);

    printf("[%s] client is going to exit\n", argv[0]);
    close(socketFD);

    pthread_cancel(listenerThread); // Added
    free(socketPtr); // Added

    return 0;
}

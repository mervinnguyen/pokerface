/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* pokersever.c: Main file for the sever			                 */
/*********************************************************************/

#include "pokerserver_core.h"
#include "gamelogic.h"

int main(int argc, char *argv[]) {
    int serverSocket, dataSocket, portNum;
    struct sockaddr_in serverAddress;
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


    pthread_mutex_init(&mapLock, NULL); // Initialize mutex
    pthread_mutex_init(&socketLock, NULL); // Initialize socket mutex

    memset(clientSockets, 0, sizeof(clientSockets)); // Initialize client sockets array

    while (1) {
        //Wait for a client to connect
        dataSocket = accept(serverSocket, NULL, NULL);
        if (dataSocket < 0) {
            fprintf(stderr, "accept failed\n");
            continue;   //Handle errors
        }

        //Creating a new thread to handle client requests
        pthread_t clientThread;
        int *dataSocketPtr = malloc(sizeof(int));
        if (dataSocketPtr == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            close(dataSocket);
            continue;
        }
        *dataSocketPtr = dataSocket;

        if (pthread_create(&clientThread, NULL, handleClient, dataSocketPtr) != 0) {
            fprintf(stderr, "client thread creation failed\n");
            close(dataSocket);
            free(dataSocketPtr);
            continue;
        }
        pthread_detach(clientThread);
    }

    close(serverSocket);
    pthread_mutex_destroy(&mapLock); // Destroy mutex
    pthread_mutex_destroy(&socketLock); // Destroy socket mutex
    return 0;
}

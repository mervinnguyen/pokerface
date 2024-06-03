#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "gui.h"
#include "pokerclient_core.h"

#define MAX_MESSAGE_LEN 255
#define PORT_NUMBER_LOWER_BOUND 1024

void getPortNum(int argc, char *const *argv, int* portNum) {
    if (argc < 3) {
        fprintf(stderr, "wrong params. Usage: %s hostname port\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *portNum = atoi(argv[2]);
    if (*portNum <= PORT_NUMBER_LOWER_BOUND) {
        fprintf(stderr, "[%s] invalid port number %d, should be greater than %d\n", argv[0], *portNum, PORT_NUMBER_LOWER_BOUND);
        exit(EXIT_FAILURE);
    }
}


/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_server.c: Unit test for server			                 */
/*********************************************************************/


#include "server.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_getPortNum() {
    char *argv[] = {"server", "8080"};
    assert(getPortNum(2, argv) == 8080);

    char *invalid_argv[] = {"server", "1023"};
    assert(getPortNum(2, invalid_argv) == -1);  
}

void test_strlen_without_null() {
    assert(strlen_without_null("test") == 4);
    assert(strlen_without_null("test\n") == 4);
    assert(strlen_without_null("") == 0);
}

void test_initializeCards() {
    char **cards = initializeCards();
    assert(cards != NULL);
    for (int i = 0; i < MAX_CARDS_PER_CLIENT; ++i) {
        assert(cards[i] != NULL);
        free(cards[i]);
    }
    free(cards);
}

void test_shuffleCards() {
    char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1] = {"A-Hearts", "2-Hearts", "3-Hearts", "4-Hearts"};
    shuffleCards(cards, 4);
    
}

void test_getFirstCardsIndex() {
    char cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1] = {"A-Hearts", "SENT", "3-Hearts", "4-Hearts"};
    assert(getFirstCardsIndex(cards, 4) == 3);
    char no_cards[MAX_CARDS_PER_CLIENT][MAX_MESSAGE_LEN + 1] = {"SENT", "SENT", "SENT", "SENT"};
    assert(getFirstCardsIndex(no_cards, 4) == -1);
}

int main() {
    test_getPortNum();
    test_strlen_without_null();
    test_initializeCards();
    test_shuffleCards();
    test_getFirstCardsIndex();

    printf("All tests passed!\n");
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CARDS 52
#define CARDS_PER_PLAYER 2
#define NUM_RANKS 13

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

typedef enum {
    PREFLOP = 0,
    FLOP = 1,
    TURN = 2,
    RIVER = 3
}ROUND;

typedef enum {
    SMALL_BLIND = 0,
    BIG_BLIND = 1,
    REGULAR = 2
}BLIND;

typedef struct {
	SUIT suit;
	RANK rank;
}Card;

typedef struct {
	struct Card cards[5];
}Hand;

typedef struct {
	struct Card cards[NUM_CARDS];
	int top;
}Deck;

typedef enum {
    FOLD = 0,
    CHECK = 1,
    CALL = 2,
    RAISE = 3
}Moves;

typedef struct {
    int chips;
    int bet;
    int raise;
    Card card1;
    Card card2;
    Moves move;
}Player;

//create a struct for the state of the game
typedef struct {
    int pot;
    ROUND round;
    int currentCall;
    int numPlayers;
    int currentPlayer;
    int numGames;
    int dealer;
    int smallBlind;
    int bigBlind;
    int raise;
    int maxBet;
    int minBet;
    int maxRaise;
    int minRaise;
    int numFolded;
    int numCalled;
    int numRaised;
    int numChecked;
    int numAllIn;
    Player players[7];
    Deck shuffleDeck;
    Deck communityCards;
}Game;

const char *suits[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const char *ranks[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

void makeDeck(Deck *deck){
    int count = 0;
    for (int suit = 0; suit < 4; suit++)
    {
        for (int rank = 2; rank < 15; rank++)
        {
            deck->cards[count].suit = suit;
            deck->cards[count].rank = rank;
            count++;
        }
    }
}

void shuffleDeck(Deck *deck)
{
    srand(time(NULL));
    for (int i = NUM_CARDS - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Card temp = deck->card[i];
        deck->cards[i] = deck->cards[j];
        deck->cards[j] = temp;
    }
}

void dealCards(Game *game)
{
    int deckIndex = 0;
    for (int i = 0; i < game->numPlayers; i++)
    {
        game->players[i].card1 = game->shuffleDeck.cards[deckIndex++];
        game->players[i].card2 = game->shuffleDeck.cards[deckIndex++];
    }

    for (int i = 0; i < 5; i++)
    {
        game->communityCards.cards[i] = game->shuffleDeck.cards[deckIndex++];
    }
    game->communityCards.top = 5;
}

int CheckPlayer(Game *game, int player){
    int priority;
    if(CheckRoyalFlush(game, player) == 1){
        priority = 10;
    }
    else if(CheckStraightFlush(game, player) == 1){
        priority = 9;
    }
    else if(CheckFourOfAKind(game, player) == 1){
        priority = 8;
    }
    else if(CheckFullHouse(game, player) == 1){
        priority = 7;
    }
    else if(CheckFlush(game, player) == 1){
        priority = 6;
    }
    else if(CheckStraight(game, player) == 1){
        priority = 5;
    }
    else if(CheckThreeOfAKind(game, player) == 1){
        priority = 4;
    }
    else if(CheckTwoPair(game, player) == 1){
        priority = 3;
    }
    else if(CheckPair(game, player) == 1){
        priority = 2;
    }
    else{
        priority = CheckHighCard(game, player);
    }

    return priority;
}

int CheckRoyalFlush(Game *game, int player){
    Deck *NewDeck;
    int i = 0;
    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    if ((a == 10 && b == 11 && c == 12 && d == 13 && e == 14) || (b == 10 && c == 11 && d == 12 && e == 13 && f == 14) || (c == 10 && d == 11 && e == 12 && f == 13 && g == 14)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckStraightFlush(Game *game, int player){
    if (CheckFlush(game, player) == 1 && CheckStraight(game, player) == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckFourOfAKind(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;
    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    if ((a == b && b == c && c == d) || (b == c && c == d && d == e) || (c == d && d == e && e == f) || (d == e && e == f && f == g)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckFullHouse(Game *game, int player){
    if (CheckThreeOfAKind(game, player) == 1 && CheckPair(game, player) == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckFlush(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;
    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    NewDeck = SortbySuit(NewDeck);

    a = NewDeck->cards[0].SUIT;
    b = NewDeck->cards[1].SUIT;
    c = NewDeck->cards[2].SUIT;
    d = NewDeck->cards[3].SUIT;
    e = NewDeck->cards[4].SUIT;
    f = NewDeck->cards[5].SUIT;
    g = NewDeck->cards[6].SUIT;

    if ((a == b && b == c && c == d && d == e) || (b == c && c == d && d == e && e == f) || (c == d && d == e && e == f && f == g)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckStraight(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;
    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    if ((e == d+1 && d == c+1 && c == b+1 && b == a+1) || (f == e+1 && e == d+1 && d == c+1 && c == b+1) || (g == f+1 && f == e+1 && e == d+1 && d == c+1)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckThreeOfAKind(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;
    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    if ((a == b && b == c) || (b == c && c == d) || (c == d && d == e) || (d == e && e == f) || (e == f && f == g)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckTwoPair(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;
        for (i=0; i<5; i++){
            NewDeck->cards[i] = game->communityCards.cards[i];
        }
    
        //this is the player's hand
        NewDeck->cards[5] = game->players[player].card1;
        NewDeck->cards[6] = game->players[player].card2;
    
        //sort the deck by rank
        NewDeck = SortbyRank(NewDeck);
    
        a = NewDeck->cards[0].RANK;
        b = NewDeck->cards[1].RANK;
        c = NewDeck->cards[2].RANK;
        d = NewDeck->cards[3].RANK;
        e = NewDeck->cards[4].RANK;
        f = NewDeck->cards[5].RANK;
        g = NewDeck->cards[6].RANK;

        //write if statements for all ways that the a-g can have two pairs
        if ((a == b && ( c == d || d == e || e == f || f == g)) || (b == c && (a == d || d == e || e == f || f == g)) || (c == d && (e == f || f == g)) || (d == e && (f == g))){
            return 1;
        }
        else{
            return 0;
        }
        
}

int CheckPair(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;

    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }

    //this is the player's hand
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    //sort the deck by rank
    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    //check if the player has a pair
    if ((a == b) || (b == c) || (c == d) || (d == e) || (e == f) || (f == g)){
        return 1;
    }
    else{
        return 0;
    }
}

int CheckHighCard(Game *game, int player){
    Deck *NewDeck;
    int a, b, c, d, e, f, g, i;

    for (i=0; i<5; i++){
        NewDeck->cards[i] = game->communityCards.cards[i];
    }

    //this is the player's hand
    NewDeck->cards[5] = game->players[player].card1;
    NewDeck->cards[6] = game->players[player].card2;

    //sort the deck by rank
    NewDeck = SortbyRank(NewDeck);

    a = NewDeck->cards[0].RANK;
    b = NewDeck->cards[1].RANK;
    c = NewDeck->cards[2].RANK;
    d = NewDeck->cards[3].RANK;
    e = NewDeck->cards[4].RANK;
    f = NewDeck->cards[5].RANK;
    g = NewDeck->cards[6].RANK;

    //check if the player has a high card

    //if f or g is a 2, return 2
    if (f == 2 || g == 2){
        return 2;
    }
    //if f or g is a 3, return 3
    else if (f == 3 || g == 3){
        return 3;
    }
    //if f or g is a 4, return 4
    else if (f == 4 || g == 4){
        return 4;
    }
    //if f or g is a 5, return 5
    else if (f == 5 || g == 5){
        return 5;
    }
    //if f or g is a 6, return 6
    else if (f == 6 || g == 6){
        return 6;
    }
    //if f or g is a 7, return 7
    else if (f == 7 || g == 7){
        return 7;
    }
    //if f or g is a 8, return 8
    else if (f == 8 || g == 8){
        return 8;
    }
    //if f or g is a 9, return 9
    else if (f == 9 || g == 9){
        return 9;
    }
    //if f or g is a 10, return 10
    else if (f == 10 || g == 10){
        return 10;
    }
    //if f or g is a 11, return 11
    else if (f == 11 || g == 11){
        return 11;
    }
    //if f or g is a 12, return 12
    else if (f == 12 || g == 12){
        return 12;
    }
    //if f or g is a 13, return 13
    else if (f == 13 || g == 13){
        return 13;
    }
    //if f or g is a 14, return 14
    else if (f == 14 || g == 14){
        return 14;
    }
}


//sort rank by rank
Deck SortbyRank(Deck *D){
    CARD A;
    int i, j;
    for (i=0; i<7; i++){
        for (j=0; j<7-i-1; j++){
            if (D->cards[j].rank > D->cards[j+1].rank){
                A = D->cards[j];
                D->cards[j] = D->cards[j+1];
                D->cards[j+1] = A;
            }
        }
    }
    return D;
}

//Sort by suit
Deck SortbySuit(Deck *D){
    CARD A;
    int i, j;
    for (i=0; i<7; i++){
        for (j=0; j<7-i-1; j++){
            if (D->cards[j].suit > D->cards[j+1].suit){
                A = D->cards[j];
                D->cards[j] = D->cards[j+1];
                D->cards[j+1] = A;
            }
        }
    }
    return D;
}

void initGame(Game *game, int numPlayers)
{
    game->numPlayers = numPlayers;
    game->round = PREFLOP;
    game->pot = 0;
    game->currentPlayer = 0;
    game->dealer = 0;
    game->smallBlind = 1;
    game->bigBlind = 2;
    game->numFolded = 0;
    game->numCalled = 0;
    game->numRaised = 0;
    game->numAllIn = 0;

    for (int i = 0; i < numPlayers; i++)
    {
        game->players[i].chips = 1000;
        game->players[i].bet = 0;
        game->players[i].raise = 0;
        game->players[i].move = CHECK;

    }

    makeDeck(&game->shuffleDeck);
    shuffleDeck(&game->shuffleDeck);
    dealCards(game);

}

void playerAction(Game *game, int playerIndex) 
{
    Player *player = &game->players[playerIndex];
    int action;

    printf("Player %d's turn. Chips: %d\n", playerIndex, player->chips);
    displayPlayerCards(player);
    displayCommunityCards(&game->communityCards);

    // Display current game state
    printf("Current pot: %d\n", game->pot);
    printf("Current call: %d\n", game->currentCall);
    
    // Check if the player can check
    if (game->currentCall == 0) 
    {
        printf("Options: 1. Check  2. Bet  3. Fold\n");
    } else 
    {
        printf("Options: 1. Call  2. Raise  3. Fold\n");
    }
    
    // Get player action
    scanf("%d", &action);

    switch (action) 
    {
        case 1:
            if (game->currentCall == 0) 
            {
                player->move = CHECK;
                printf("Player %d checks.\n", playerIndex);
            } 
            else 
            {
                player->move = CALL;
                player->chips -= game->currentCall;
                player->bet += game->currentCall;
                game->pot += game->currentCall;
                printf("Player %d calls.\n", playerIndex);
            }
            break;

        case 2:
            if (game->currentCall == 0) 
            {
                // Place a bet
                int bet;
                printf("Enter bet amount: ");
                scanf("%d", &bet);
                player->chips -= bet;
                player->bet += bet;
                game->pot += bet;
                game->currentCall = bet;
                game->maxBet = bet;
                player->move = RAISE;
                printf("Player %d bets %d chips.\n", playerIndex, bet);
            } 
            else 
            {
                // Raise
                int raise;
                printf("Enter raise amount: ");
                scanf("%d", &raise);
                player->chips -= (game->currentCall + raise);
                player->bet += (game->currentCall + raise);
                game->pot += (game->currentCall + raise);
                game->currentCall += raise;
                game->maxBet += raise;
                player->move = RAISE;
                printf("Player %d raises by %d chips.\n", playerIndex, raise);
            }
            break;

        case 3:
            player->move = FOLD;
            printf("Player %d folds.\n", playerIndex);
            break;

        default:
            printf("Invalid action. Try again.\n");
            playerAction(game, playerIndex); // Recursively ask for a valid action
    }
}

void startGame(Game *game)
{
    while(game->round <= RIVER)
    {
        for (int i = 0; i < game->numPlayers; i++)
        {
            if (game->players[i].move != FOLD)
            {
                playerAction(game, i);
            }
        }
        game->round++;

        if (game->round == FLOP)
        {
            game->communityCards.top = 3;
        }
        else if (game->round == TURN)
        {
            game.communityCards.top = 4;
        }
        else if (game->round == RIVER)
        {
            game->communityCards.top = 5;
        }
    }
}

void displayPlayerCards(Player *player)
{
    printf("Player's cards are: %s of %s, %s of %s\n", ranks[player->card1.rank - 2], suits[player->card1.suit], ranks[player->card2.rank - 2], suits[player->card2.suit]);
}

void displayCommunityCards(Deck *communityCards) 
{
    printf("Community Cards: ");
    for (int i = 0; i < communityCards->top; i++)
    {
        printf("%s of %s ", ranks[communityCards->cards[i].rank - 2], suits[communityCards->cards[i].suit]);   
    }
    printf("\n");
}


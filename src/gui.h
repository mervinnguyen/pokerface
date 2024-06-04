/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                     	 */
/* GUI.h: Structs + Functionality of GUI header file				 */
/*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <assert.h>
// #include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

// Contstants will be moved to constants.h later
// Window width & height is divided by 1.5 for ease of programming on a smaller screen
#define WINDOW_WIDTH 1280/1.5
#define WINDOW_HEIGHT 720/1.5
// Used for video
// #define WINDOW_WIDTH 1280/2.5
// #define WINDOW_HEIGHT 720/2.5
#define CARD_WIDTH (WINDOW_WIDTH/15)
#define CARD_HEIGHT (WINDOW_HEIGHT/6)
#define NUMBER_OF_SEATS 4
#define STRING_BUFFER 100
// #define LENGTH_OF_MAX_RANK_PLUS_1 10
// #define LENGTH_OF_MAX_SUIT_PLUS_1 10

// // Structure that holds necessary pointers in order to relay user input and update state
// typedef struct {
//     GtkWidget *entry;
//     gpointer other_data;
// } CallbackData;
// // CallbackData *callback_data = g_malloc(sizeof(CallbackData));




/* Function Declarations */
// CreateClientWindow creates the GUI for the client side of the poker program
GtkWidget *CreateClientWindow(int *argc, char **argv[], char dealt_cards[5][STRING_BUFFER]);
// delete_event is connected whenever the x on the GUI window is clicked.

#endif
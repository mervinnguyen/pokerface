/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                     	 */
/* GUI.h: Structs + Functionality of GUI header file				 */
/*********************************************************************/
#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

// Contstants will be moved to constants.h later
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600
#define NUMBER_OF_SEATS 4
#define STRING_BUFFER 100

// // Structure that holds necessary pointers in order to relay user input and update state
// typedef struct {
//     GtkWidget *entry;
//     gpointer other_data;
// } CallbackData;
// // CallbackData *callback_data = g_malloc(sizeof(CallbackData));




/* Function Declarations */
// CreateClientWindow creates the GUI for the client side of the poker program
GtkWidget *CreateClientWindow(int *argc, char **argv[]);
// delete_event is connected whenever the x on the GUI window is clicked.

#endif
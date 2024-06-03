/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_gui.c: Unit test for GUI	                             */
/*********************************************************************/
// #include <unistd.h>
// #include <time.h>
#include "gui.h"

/*
Links:
https://zetcode.com/gui/gtk2/
https://docs.huihoo.com/gtk/tutorial/2.0/index.html
https://www.manpagez.com/html/gtk2/gtk2-2.24.29/
https://docs.gtk.org/gtk3/index.html
https://developer.gnome.org/documentation/tools/valgrind.html
valgrind --leak-check=full --suppressions=/usr/share/glib-2.0/valgrind/glib.supp ./GTK_ClockClient bondi 10000
*/
/*
TODO LIST: (player)
import a poker table for the background
add player names, points, and action 


Create a structure to remove the use of gobal variables
Next expand the structure to accept the combo box, int to store the combo box.
Expand it so that I'm able to switch between two windows at the click of the button.

Set the title to the title of the program by passing the user input which would be argv[0]

Control Flow for Client Side GUI:
	Start with the creation of the main menu it will return the pointer to the created window.
	Like in the ClockServer it will check the inputs from the server.
	Therefore the GUI will only update when it's in the game state and won't update if it timesout.
*/

// // UpdateWindow From Prof Doemer's Sample Code
// void UpdateWindow(void)		/* render the window on screen */
// {
//    /* this server has it's own main loop for handling client connections;
//     * as such, it can't have the usual GUI main loop (gtk_main);
//     * instead, we call this UpdateWindow function on regular basis
//     */
//     while(gtk_events_pending())
//     {
// 	gtk_main_iteration();
//     }
// } /* end of UpdateWindow */

int main (int argc, char *argv[])
{
	// GTK Variables
	GtkWidget *window = NULL;	// Main window

	// Array used to print the dealer cards on the poker table in the GUI
	// Note: Inputing incorrect string notation will result in a card shadow to be created instead on the GUI
	// Notation: RANK_of_SUIT; ex: ace_of_spades
	char dealt_cards[5][STRING_BUFFER] = {"ace_of_spades", "8_of_hearts", "jack_of_diamonds", "4_of_clubs","back_card"};

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
		fprintf(stderr, "GTKWidget pointer to window has not been returned.\n");
        // Error Code #1
		return 1;
    }

	// Update the GUI window every 0.25 seconds while the window is alive
	// int timeout = 250000;
	// while(!window)
	// {	
	// 	UpdateWindow();
	// 	printf("Sleeping for 0.25 seconds...\n");
	// 	sleep(1); // 250,000 microseconds = 0.25 seconds
	// 	printf("0.25 seconds have passed.\n");
	// }

	// No Errors
	return 0 ;
}














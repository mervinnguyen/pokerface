/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_gui.c: Unit test for GUI	                             */
/*********************************************************************/

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


int main (int argc, char *argv[])
{
	// GTK Variables
	GtkWidget *window = NULL;	// Main window
	
	// Creates a GUI for client
	window = CreateClientWindow(&argc, &argv);
	// Checks that a window pointer has been returned
	if (!window)
    {
		// Prints error to standard error stream
		fprintf(stderr, "GTKWidget ointer to window has not been returned.\n");
        // Error Code #1
		return 1;
    }

	// No Errors
	return 0 ;
}












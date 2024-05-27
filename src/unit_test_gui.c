/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* unit_test_gui.c: Unit test for GUI	                             */
/*********************************************************************/


#include "gui.h"

/*
https://zetcode.com/gui/gtk2/
https://docs.huihoo.com/gtk/tutorial/2.0/index.html
https://www.manpagez.com/html/gtk2/gtk2-2.24.29/
https://docs.gtk.org/gtk3/index.html
https://developer.gnome.org/documentation/tools/valgrind.html
valgrind --leak-check=full --suppressions=/usr/share/glib-2.0/valgrind/glib.supp ./GTK_ClockClient bondi 10000
*/
/*
TODO LIST: (player)
Create a structure to store the state, vbox containing the entry boxes, char arrays to store the username and password.
Next expand the structure to accept the combo box, int to store the combo box.
Expand it so that I'm able to switch between two windows at the click of the button.

Set the title to the title of the program by passing the user input which would be argv[0]

In order to switch windows try using the state to determine when to switch as well as which window is displayed at the end

Control Flow for Client Side GUI:
	Start with the creation of the main menu it will return the pointer to the created window.
	Like in the ClockServer it will check the inputs from the server.
	Therefore the GUI will only update when it's in the game state and won't update if it timesout.
*/


int main (int argc, char *argv[])
{
	// Remindar - get the return and check if the window exists
	CreateClientWindow(&argc, &argv);

	// No Errors
	return 0 ;
}












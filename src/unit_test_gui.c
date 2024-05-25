
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 500
#define NUMBER_OF_SEATS 4
/*
https://zetcode.com/gui/gtk2/
https://docs.huihoo.com/gtk/tutorial/2.0/index.html
https://www.manpagez.com/html/gtk2/gtk2-2.24.29/
https://docs.gtk.org/gtk3/index.html
*/
/*
TODO LIST: (player)
Create a structure to store the state, vbox containing the entry boxes, char arrays to store the username and password.
Next expand the structure to accept the combo box, int to store the combo box.
Expand it so that I'm able to switch between two windows at the click of the button.
*/


static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data)
{
    /* If you return FALSE in the "delete_event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

    g_print ("Delete event occurred!\n");
	g_print ("Closing Xming Window!\n");
	gtk_widget_destroy(widget);
    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete_event". */
    return FALSE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static void button1_clicked(GtkWidget *widget, gpointer data)
{
	int *value_ptr = (int *)data;
	*(value_ptr) = 1;

	printf("button 1 clicked\n");
	gtk_widget_destroy(widget);
    // gtk_widget_hide(widget);
}

// // Structure that holds necessary pointers in order to relay user input and update state
// typedef struct {
//     GtkWidget *entry;
//     gpointer other_data;
// } CallbackData;
// // CallbackData *callback_data = g_malloc(sizeof(CallbackData));

int main (int argc, char *argv[])
{
	// GTK Variables
	GtkWidget *window = NULL;					// Main window
	GtkWidget *vbox_main_menu = NULL;			// Allignment
	GtkWidget *label_main_menu = NULL;			// Main Menu Label
	GtkWidget *tablealign = NULL;				// Alignment for Username/Password table
	GtkWidget *table_main_menu = NULL;			// Table Allignment
	GtkWidget *label_username = NULL;			// Username Label
	GtkWidget *label_password = NULL;			// Password Label
	GtkWidget *entry_username = NULL;			// Entry textbox for username
	GtkWidget *entry_password = NULL;			// Entry textbox for password
	GtkWidget *comboalign = NULL;				// Alignment for dropdown selection
	GtkWidget *combo_seat_dropdown = NULL;		// Dropdown text selection for seat number
	GtkWidget *buttonalign = NULL;				// Alignment for the play button
	GtkWidget *button_play = NULL;				// Play button
	GdkPixbuf *pokerIcon = NULL;
	int state = 0;
	char seat[] = "Seat _";
	// char username[MAX_STRING_BUFFER];
	printf("state: %d\n",state);
	
	// Boolean used to determine if GTK has been initalized correctly
	bool initGTK = 0;

	// Initalizes GTK
	initGTK = gtk_init_check(&argc,&argv);
	if (initGTK != 1)
	{
		// Prints error to standard error stream
		fprintf(stderr, "Error Code: %d\nCan not open external display!\n", initGTK);
		// Error Code #1 - Display can not be opened
		return 1;
	}

	// Create a new window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Check if the window pointer is available ^^^

	// Center GTK window
	gtk_window_set_title(GTK_WINDOW(window), "Poker");
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	// Add poker icon to window
	pokerIcon = gdk_pixbuf_new_from_file("gui_images/PokerIcon.png", NULL); 
  	gtk_window_set_icon(GTK_WINDOW(window), pokerIcon);

	// Create a vertical box for alignment
	vbox_main_menu = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vbox_main_menu);

	// Create a label that displays the ASCII main menu
	label_main_menu = gtk_label_new("Main Menu");
	gtk_label_set_line_wrap(GTK_LABEL(label_main_menu), TRUE);
	gtk_label_set_justify(GTK_LABEL(label_main_menu), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vbox_main_menu), label_main_menu, TRUE, TRUE, 0);


	// Aligns the Username/Password table to the center
	tablealign = gtk_alignment_new(0.455, 1, 0, 0);
	gtk_box_pack_start(GTK_BOX(vbox_main_menu), tablealign, TRUE, TRUE, 0);

	// Create a table for aligning the Username/Password section
	table_main_menu = gtk_table_new(2, 2, TRUE);
		// gtk_table_set_row_spacings(GTK_TABLE(table_main_menu), 2);
  		// gtk_table_set_col_spacings(GTK_TABLE(table_main_menu), 2);
	// Create entries for user to input a username and password
	label_username = gtk_label_new("Username:");
	label_password = gtk_label_new("Password:");
	entry_username = gtk_entry_new();;
	entry_password = gtk_entry_new();;
	gtk_table_attach(GTK_TABLE(table_main_menu), label_username, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(table_main_menu), label_password, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(table_main_menu), entry_username, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	gtk_table_attach(GTK_TABLE(table_main_menu), entry_password, 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	// Adds the Username/Password table to the table alignment
	gtk_container_add(GTK_CONTAINER(tablealign), table_main_menu);

	// Aligns the dropdown menu to the center
	comboalign = gtk_alignment_new(0.5, 0, 0.246, 0.3);
	gtk_box_pack_start(GTK_BOX(vbox_main_menu), comboalign, TRUE, TRUE, 0);

	// Create a combo box text so that users can select a seat
	combo_seat_dropdown = gtk_combo_box_new_text();
	for (int i; i<NUMBER_OF_SEATS; i++)
	{
		seat[5] = '1' + i; 
		printf("%s\n", seat);
		gtk_combo_box_append_text(GTK_COMBO_BOX(combo_seat_dropdown), seat);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(combo_seat_dropdown), 0);
	// Adds the dropdown menu to the combo alignment
	gtk_container_add(GTK_CONTAINER(comboalign), combo_seat_dropdown);
	// gtk_box_pack_start(GTK_BOX(vbox_main_menu), combo_seat_dropdown, TRUE, TRUE, 0);


	// Aligns the button to the center
	buttonalign = gtk_alignment_new(0.5, 0.5, 0.2, 0.1);
	gtk_box_pack_start(GTK_BOX(vbox_main_menu), buttonalign, TRUE, TRUE, 0);
	
	// Creates a button to play the game
	button_play = gtk_button_new_with_label("Play");
	gtk_widget_set_tooltip_text(button_play, "Click to start game");
	// gtk_box_pack_start(GTK_BOX(vbox_main_menu), button, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(buttonalign), button_play);
	
	// Show widgets through Xming
    gtk_widget_show_all(window);
	
	// When the x button is clicked closes the window
	g_signal_connect (G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
	// After the delete returns false a destory event occurs and pass control is then passed back to main
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL); 
	
	// Do something after the button is clicked
	// button1_clicked(button);
	g_signal_connect(G_OBJECT(button_play), "clicked", G_CALLBACK(button1_clicked), &state); 

	g_object_unref(pokerIcon);

	// GTK set to sleep (GTK now waits until an event occurs)
    gtk_main();

	printf("test\n");
	printf("state: %d\n",state);

	// No Errors
	return 0 ;
}










// GdkPixbuf *create_pixbuf(const gchar * filename) {
    
//    GdkPixbuf *pixbuf;
//    GError *error = NULL;
//    pixbuf = gdk_pixbuf_new_from_file(filename, &error);
   
//    if (!pixbuf) {
       
//       fprintf(stderr, "%s\n", error->message);
//       g_error_free(error);
//    }

//    return pixbuf;
// }

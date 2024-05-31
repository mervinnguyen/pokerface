/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* GUI.c: source file for GUI creation	                             */
/*********************************************************************/

#include "gui.h"

// Temporary Global Variables - To get entry box inputs from user and store them in a char array
GtkWidget *entry_username = NULL;			// Entry textbox for username
// Variables that will stor the User's inputs from the main menu
char client_username[STRING_BUFFER] = "";

/* Static Function Declarations */
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
// destroy is connected whenever a destory event occurs (whenever delete_event returns FALSE)
static void destroy(GtkWidget *widget, gpointer data);
// update_seat is connected whenever the user selects a new seat from the drop down menu and it saves the seat for the current user into an integer
static void update_seat(GtkComboBox *combo_seat_dropdown, int *client_seat);
// button1_clicked us connected whenever the play button on the main menu is clicked. It saves the username and password the user has entered and switches to the game window
static void button1_clicked(GtkWidget *widget, gpointer data);


GtkWidget *CreateClientWindow(int *argc, char **argv[])
{
	// GTK Variables
	GtkWidget *window = NULL;					// Main window
	GtkWidget *vertical_alignment = NULL;		// Allignment
	GtkWidget *label_main_menu = NULL;			// Main Menu Label
	GtkWidget *table_alignment = NULL;			// Alignment for Username/Password table
	GtkWidget *table_main_menu = NULL;			// Table Allignment
	GtkWidget *label_username = NULL;			// Username Label
	GtkWidget *label_password = NULL;			// Password Label
	// GtkWidget *entry_username = NULL;			// Entry textbox for username
	GtkWidget *entry_password = NULL;			// Entry textbox for password
	GtkWidget *combo_alignment = NULL;			// Alignment for dropdown selection
	GtkWidget *combo_seat_dropdown = NULL;		// Dropdown text selection for seat number
	GtkWidget *button_alignment = NULL;			// Alignment for the play button
	GtkWidget *button_play = NULL;				// Play button
	GdkPixbuf *pokerIcon = NULL;
	int state = 0;
	char seat[] = "Seat _";
	// Variables that will stor the User's inputs from the main menu
	// The default seat number is 1.
	int client_seat = 1;

	// char username[MAX_STRING_BUFFER];
	printf("state: %d\n",state);
	
	// Boolean used to determine if GTK has been initalized correctly
	bool initGTK = 0;

	// Initalizes GTK
	initGTK = gtk_init_check(argc,argv);
	if (initGTK != 1)
	{
		// Prints error to standard error stream
		fprintf(stderr, "Error Code: %d\nCan not open external display!\n", initGTK);
		// Error Code #1 - Display can not be opened
		exit(1);
	}

	// Create a new window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Check if the window pointer is available ^^^

	// Update the settings for the window
	gtk_window_set_title(GTK_WINDOW(window), "Poker");
	gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
	// Center GTK window
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	// Add poker icon to window
	pokerIcon = gdk_pixbuf_new_from_file("gui_images/PokerIcon.png", NULL); 
  	gtk_window_set_icon(GTK_WINDOW(window), pokerIcon);

	// Create a vertical box for alignment
	vertical_alignment = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(window), vertical_alignment);

	// Create a label that displays the ASCII main menu
	label_main_menu = gtk_label_new("Main Menu");
	gtk_label_set_line_wrap(GTK_LABEL(label_main_menu), TRUE);
	gtk_label_set_justify(GTK_LABEL(label_main_menu), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(vertical_alignment), label_main_menu, TRUE, TRUE, 0);


	// Aligns the Username/Password table to the center
	table_alignment = gtk_alignment_new(0.455, 1, 0, 0);
	gtk_box_pack_start(GTK_BOX(vertical_alignment), table_alignment, TRUE, TRUE, 0);

	// Create a table for aligning the Username/Password section
	table_main_menu = gtk_table_new(2, 2, TRUE);
		// gtk_table_set_row_spacings(GTK_TABLE(table_main_menu), 2);
  		// gtk_table_set_col_spacings(GTK_TABLE(table_main_menu), 2);
	// Create entries for user to input a username and password
	label_username = gtk_label_new("Username:");
	label_password = gtk_label_new("Password:");
	entry_username = gtk_entry_new();
	entry_password = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(entry_password), FALSE);
	gtk_table_attach(GTK_TABLE(table_main_menu), label_username, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(table_main_menu), label_password, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(table_main_menu), entry_username, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	gtk_table_attach(GTK_TABLE(table_main_menu), entry_password, 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	// Adds the Username/Password table to the table alignment
	gtk_container_add(GTK_CONTAINER(table_alignment), table_main_menu);

	// Aligns the dropdown menu to the center
	combo_alignment = gtk_alignment_new(0.5, 0, 0.246, 0.3);
	gtk_box_pack_start(GTK_BOX(vertical_alignment), combo_alignment, TRUE, TRUE, 0);

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
	gtk_container_add(GTK_CONTAINER(combo_alignment), combo_seat_dropdown);
	// gtk_box_pack_start(GTK_BOX(vertical_alignment), combo_seat_dropdown, TRUE, TRUE, 0);

	// Aligns the button to the center
	button_alignment = gtk_alignment_new(0.5, 0.5, 0.2, 0.1);
	gtk_box_pack_start(GTK_BOX(vertical_alignment), button_alignment, TRUE, TRUE, 0);
	
	// Creates a button to play the game
	button_play = gtk_button_new_with_label("Play");
	gtk_widget_set_tooltip_text(button_play, "Click to start game");
	// gtk_box_pack_start(GTK_BOX(vertical_alignment), button, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(button_alignment), button_play);
	
	// Show widgets through Xming
    gtk_widget_show_all(window);
	
	// When the x button is clicked closes the window
	g_signal_connect (G_OBJECT(window), "delete_event", G_CALLBACK(delete_event), NULL);
	// After the delete returns false a destroy event occurs and pass control is then passed back to main
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL); 
	
	// Update the seat number whenever the combo box has been changed
    g_signal_connect(combo_seat_dropdown, "changed", G_CALLBACK(update_seat), &client_seat);

	// Do something after the button is clicked
	// button1_clicked(button);
	g_signal_connect(G_OBJECT(button_play), "clicked", G_CALLBACK(button1_clicked), &state); 

	g_object_unref(pokerIcon);

	// GTK set to sleep (GTK now waits until an event occurs)
    gtk_main();

	printf("test\n");
	printf("state: %d\n",state);
	printf("Client Username: %s\n", client_username);
	printf("Client Seat: %d\n", client_seat);

	return window;
}

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

// Updates the seat for the current user
static void update_seat(GtkComboBox *combo_seat_dropdown, int *client_seat)
{
	printf("Current Seat: %s\n",gtk_combo_box_get_active_text(combo_seat_dropdown));
	// Copy the seat number from the new selected text
	int number_assigned = sscanf(gtk_combo_box_get_active_text(combo_seat_dropdown), "Seat %d", client_seat);

	assert(number_assigned == 1);
	// Fatal error goes here as sscanf is unsuccessful in copying the int from the text
	// if(number_assigned != 1)
}

static void button1_clicked(GtkWidget *widget, gpointer data)
{
	int *value_ptr = (int *)data;
	*(value_ptr) = 1;

	// Copy the username from the username entry box into a character array to be used later
	snprintf(client_username, sizeof(client_username),"%s",gtk_entry_get_text((GtkEntry *)entry_username));
	printf("button 1 clicked\n");
	// 

	// gtk_widget_destroy(widget);
    gtk_widget_hide(widget);
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
/*********************************************************************/
/* Poker Project, for EECS 22L, Spring 2024                   		 */
/* GUI.c: source file for GUI creation	                             */
/*********************************************************************/

#include "gui.h"

// Temporary Global Variables - To get entry box inputs from user and store them in a char array
GtkWidget *CMM_ENTRY_username = NULL;			// Entry textbox for username
GtkWidget *CMM_ENTRY_password = NULL;			// Entry textbox for password
// Variables that will stor the User's inputs from the main menu
char client_username[STRING_BUFFER] = "";
char client_password[STRING_BUFFER] = "";
// Testing Window Switching with a button click
GtkWidget *Client_NOTEBOOK = NULL;		// Top level notebook to switch between the main menu and the game menu

/* Static Function Declarations */
static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data);
// destroy is connected whenever a destory event occurs (whenever delete_event returns FALSE)
static void destroy(GtkWidget *widget, gpointer data);
// update_seat is connected whenever the user selects a new seat from the drop down menu and it saves the seat for the current user into an integer
static void update_seat(GtkComboBox *CMM_COMBO_seat_dropdown, int *client_seat);
// button1_clicked us connected whenever the play button on the main menu is clicked. It saves the username and password the user has entered and switches to the game window
static void button1_clicked(GtkWidget *widget, gpointer data);


GtkWidget *CreateClientWindow(int *argc, char **argv[])
{
	// GTK Variables
	GtkWidget *Client_WINDOW = NULL;		// Main client window
	GtkWidget *Client_notebook_PAGE_1 = NULL;	// Notebook page #1
	GtkWidget *Client_notebook_PAGE_2 = NULL;	// Notebook page #1

	// GTK Variables for the Client Main Menu (CMM)
	GtkWidget *CMM_vertical_ALIGNMENT = NULL;		// Allignment
	GtkWidget *CMM_menu_LABEL = NULL;			// Main Menu Label
	GtkWidget *CMM_input_table_ALIGNMENT = NULL;	// Alignment for Username/Password table
	GtkWidget *CMM_input_TABLE_menu = NULL;			// Table widget for Username/Password
	GtkWidget *CMM_LABEL_username = NULL;			// Username Label
	GtkWidget *CMM_LABEL_password = NULL;			// Password Label
	// GtkWidget *CMM_ENTRY_username = NULL;			// Entry textbox for username
	// GtkWidget *CMM_ENTRY_password = NULL;			// Entry textbox for password
	GtkWidget *CMM_combo_ALIGNMENT = NULL;			// Alignment for dropdown selection
	GtkWidget *CMM_COMBO_seat_dropdown = NULL;		// Dropdown text selection for seat number
	GtkWidget *CMM_play_button_ALIGNMENT = NULL;	// Alignment for the play button
	GtkWidget *CMM_BUTTON_play = NULL;				// Play button

	// GTK Variables for the Client GAME Menu (CGM)
	GtkWidget *CGM_vertical_ALIGNMENT = NULL;		// Allignment
	GtkWidget *CGM_menu_LABEL = NULL;				// Main Menu Label

	// Miscellaneous GTK variables
	GdkPixbuf *pokerIcon = NULL;	// window icon
	GdkColor CMM_background_COLOR;	// Background Color for CMM
	GdkColor CGM_background_COLOR;	// Background Color for CGM

	// Non-GTK variables
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
	Client_WINDOW = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	//Check if the window pointer is available ^^^

	// Update the settings for the window
	gtk_window_set_title(GTK_WINDOW(Client_WINDOW), "Poker");
	gtk_window_set_default_size(GTK_WINDOW(Client_WINDOW), WINDOW_WIDTH, WINDOW_HEIGHT);
	// Center GTK window
	gtk_window_set_position(GTK_WINDOW(Client_WINDOW), GTK_WIN_POS_CENTER);
	// gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	// Add poker icon to window
	pokerIcon = gdk_pixbuf_new_from_file("gui_images/PokerIcon.png", NULL); 
  	gtk_window_set_icon(GTK_WINDOW(Client_WINDOW), pokerIcon);

	// Create the client notebook to switch between the different windows
	Client_NOTEBOOK = gtk_notebook_new();
	// Turn off tabs
	gtk_notebook_set_show_tabs(GTK_NOTEBOOK(Client_NOTEBOOK), FALSE);
	gtk_container_add(GTK_CONTAINER(Client_WINDOW), Client_NOTEBOOK);
	

	/* Main Menu Creation */
	// Create the first notebook page
	Client_notebook_PAGE_1 = gtk_event_box_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(Client_NOTEBOOK), Client_notebook_PAGE_1, NULL);
	// Change Notebook Color
    gdk_color_parse("#f5f5f5", &CMM_background_COLOR); // Parse color in hexadecimal format
    gtk_widget_modify_bg(Client_notebook_PAGE_1, GTK_STATE_NORMAL, &CMM_background_COLOR);
	
	// Create a vertical box for alignment
	CMM_vertical_ALIGNMENT = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(Client_notebook_PAGE_1), CMM_vertical_ALIGNMENT);

	// Create a label that displays the ASCII main menu
	CMM_menu_LABEL = gtk_label_new("Main Menu");
	gtk_label_set_line_wrap(GTK_LABEL(CMM_menu_LABEL), TRUE);
	gtk_label_set_justify(GTK_LABEL(CMM_menu_LABEL), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), CMM_menu_LABEL, TRUE, TRUE, 0);

	// Aligns the Username/Password table to the center
	CMM_input_table_ALIGNMENT = gtk_alignment_new(0.455, 1, 0, 0);
	gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), CMM_input_table_ALIGNMENT, TRUE, TRUE, 0);

	// Create a table for aligning the Username/Password section
	CMM_input_TABLE_menu = gtk_table_new(2, 2, TRUE);
		// gtk_table_set_row_spacings(GTK_TABLE(CMM_input_TABLE_menu), 2);
  		// gtk_table_set_col_spacings(GTK_TABLE(CMM_input_TABLE_menu), 2);
	// Create entries for user to input a username and password
	CMM_LABEL_username = gtk_label_new("Username:");
	CMM_LABEL_password = gtk_label_new("Password:");
	CMM_ENTRY_username = gtk_entry_new();
	CMM_ENTRY_password = gtk_entry_new();
	gtk_entry_set_visibility(GTK_ENTRY(CMM_ENTRY_password), FALSE);
	gtk_table_attach(GTK_TABLE(CMM_input_TABLE_menu), CMM_LABEL_username, 0, 1, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(CMM_input_TABLE_menu), CMM_LABEL_password, 0, 1, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 0, 5);
	gtk_table_attach(GTK_TABLE(CMM_input_TABLE_menu), CMM_ENTRY_username, 1, 2, 0, 1, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	gtk_table_attach(GTK_TABLE(CMM_input_TABLE_menu), CMM_ENTRY_password, 1, 2, 1, 2, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 0);
	// Adds the Username/Password table to the table alignment
	gtk_container_add(GTK_CONTAINER(CMM_input_table_ALIGNMENT), CMM_input_TABLE_menu);

	// Aligns the dropdown menu to the center
	CMM_combo_ALIGNMENT = gtk_alignment_new(0.5, 0, 0.246, 0.3);
	gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), CMM_combo_ALIGNMENT, TRUE, TRUE, 0);

	// Create a combo box text so that users can select a seat
	CMM_COMBO_seat_dropdown = gtk_combo_box_new_text();
	for (int i; i<NUMBER_OF_SEATS; i++)
	{
		seat[5] = '1' + i; 
		printf("%s\n", seat);
		gtk_combo_box_append_text(GTK_COMBO_BOX(CMM_COMBO_seat_dropdown), seat);
	}
	gtk_combo_box_set_active(GTK_COMBO_BOX(CMM_COMBO_seat_dropdown), 0);
	// Adds the dropdown menu to the combo alignment
	gtk_container_add(GTK_CONTAINER(CMM_combo_ALIGNMENT), CMM_COMBO_seat_dropdown);
	// gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), CMM_COMBO_seat_dropdown, TRUE, TRUE, 0);

	// Aligns the button to the center
	CMM_play_button_ALIGNMENT = gtk_alignment_new(0.5, 0.5, 0.2, 0.1);
	gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), CMM_play_button_ALIGNMENT, TRUE, TRUE, 0);
	
	// Creates a button to play the game
	CMM_BUTTON_play = gtk_button_new_with_label("Play");
	gtk_widget_set_tooltip_text(CMM_BUTTON_play, "Click to start game");
	// gtk_box_pack_start(GTK_BOX(CMM_vertical_ALIGNMENT), button, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(CMM_play_button_ALIGNMENT), CMM_BUTTON_play);
	

	
	// When the x button is clicked closes the window
	g_signal_connect (G_OBJECT(Client_WINDOW), "delete_event", G_CALLBACK(delete_event), NULL);
	// After the delete returns false a destroy event occurs and pass control is then passed back to main
	g_signal_connect(G_OBJECT(Client_WINDOW), "destroy", G_CALLBACK(destroy), NULL); 
	// Update the seat number whenever the combo box has been changed
    g_signal_connect(CMM_COMBO_seat_dropdown, "changed", G_CALLBACK(update_seat), &client_seat);
	// Do something after the button is clicked
	// button1_clicked(button);
	g_signal_connect(G_OBJECT(CMM_BUTTON_play), "clicked", G_CALLBACK(button1_clicked), &state); 


	/* Game Menu Creation */
	// Create the second notebook page
	Client_notebook_PAGE_2 = gtk_event_box_new();
	gtk_notebook_append_page(GTK_NOTEBOOK(Client_NOTEBOOK), Client_notebook_PAGE_2, NULL);
	// Change Notebook Color
    gdk_color_parse("#f5f5f5", &CGM_background_COLOR); // Parse color in hexadecimal format
    gtk_widget_modify_bg(Client_notebook_PAGE_2, GTK_STATE_NORMAL, &CGM_background_COLOR);

	// Create a vertical box for alignment
	CGM_vertical_ALIGNMENT = gtk_vbox_new(FALSE, 10);
	gtk_container_add(GTK_CONTAINER(Client_notebook_PAGE_2), CGM_vertical_ALIGNMENT);

	// Create a label that displays the ASCII main menu
	CGM_menu_LABEL = gtk_label_new("Game Menu");
	gtk_label_set_line_wrap(GTK_LABEL(CGM_menu_LABEL), TRUE);
	gtk_label_set_justify(GTK_LABEL(CGM_menu_LABEL), GTK_JUSTIFY_CENTER);
	gtk_box_pack_start(GTK_BOX(CGM_vertical_ALIGNMENT), CGM_menu_LABEL, TRUE, TRUE, 0);



	// Show widgets through Xming
	gtk_widget_show_all(Client_WINDOW);


	g_object_unref(pokerIcon);

	// GTK set to sleep (GTK now waits until an event occurs)
    gtk_main();

	printf("test\n");
	printf("state: %d\n",state);
	printf("Client Username: %s\n", client_username);
	printf("Client Password: %s\n", client_password);
	printf("Client Seat: %d\n", client_seat);

	return Client_WINDOW;
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
static void update_seat(GtkComboBox *CMM_COMBO_seat_dropdown, int *client_seat)
{
	printf("Current Seat: %s\n",gtk_combo_box_get_active_text(CMM_COMBO_seat_dropdown));
	// Copy the seat number from the new selected text
	int number_assigned = sscanf(gtk_combo_box_get_active_text(CMM_COMBO_seat_dropdown), "Seat %d", client_seat);

	assert(number_assigned == 1);
	// Fatal error goes here as sscanf is unsuccessful in copying the int from the text
	// if(number_assigned != 1)
}

static void button1_clicked(GtkWidget *widget, gpointer data)
{
	int *value_ptr = (int *)data;
	*(value_ptr) = 1;

	// Copy the username from the username entry box into a character array to be used later
	snprintf(client_username, sizeof(client_username),"%s",gtk_entry_get_text((GtkEntry *)CMM_ENTRY_username));
	// Copy the password from the password entry box into a character array to be used later
	snprintf(client_password, sizeof(client_password),"%s",gtk_entry_get_text((GtkEntry *)CMM_ENTRY_password));
	printf("button 1 clicked\n");
	
	// Go to the game menu
	gtk_notebook_set_current_page(GTK_NOTEBOOK(Client_NOTEBOOK), 1);

	// gtk_widget_destroy(widget);
    // gtk_widget_hide(widget);

	// Working switch between windows
	// gtk_widget_show_all(window_client_game);
	// gtk_widget_hide(window);
	
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
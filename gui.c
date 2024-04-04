// ncurses.h includes stdio.h
#include <ncurses.h> 
#include <string.h>

#define NUMWINDOWS 4

WINDOW* createNewWin(int height, int width, int starty, int startx);
void destroyWin(WINDOW* localWin);
float getStartY(int rows, int height, float position);
float getStartX(int cols, int width, float position);
void getCommand(char* userIn, WINDOW* smallWin);
void printInventory(WINDOW* smallWin, int inventory[], int numOfItems);

int main(void){

	char msg[] = "KRONK!";
	char exitHint[] = "PRESS q TO EXIT!";
	// Inventory, we will start with 20 possible items
	int inventory[20];
	inventory[0] = 1;
	inventory[1] = 2;
	// Number of items we have in our inventory currently
	int inventoryNumCounter = 2;
	
	// Variables for getmaxyx
	int rows, cols;

	// Make a smaller window
	WINDOW* dWin;
	WINDOW* aWin;
	WINDOW* mWin;
    WINDOW* iWin;

	// Character input for the user to interact with the program
	int ch;
	// x / y pos for windows
	int starty1, startx1, starty2, startx2, 
		starty3, startx3, starty4, startx4;
	// Initalize screen
	initscr();
	// Disable echoing of input
	noecho();
	// Making colorpairs
	// Pair one with foreground and background
	start_color();
	// Get terminal variables
	getmaxyx(stdscr, rows, cols);
	
	int HEIGHT, WIDTH;

	HEIGHT = rows / 1.4;
	WIDTH  = cols / 5;
	// Special colors r,g,b
	init_color(COLOR_RED, 700, 0, 0);
	init_color(COLOR_CYAN, 0, 700, 700);
	init_color(COLOR_GREEN, 0, 700, 0);
	init_color(COLOR_BLUE, 0, 0, 700);
	init_color(COLOR_BLACK, 0, 0, 0);

	// Setting color of main window
	// wbkgd(stdscr, COLOR_PAIR(1));
	// Setting colors of smaller windows
	init_pair(1, COLOR_WHITE,   COLOR_BLACK);
	init_pair(2, COLOR_WHITE,    COLOR_CYAN);
	init_pair(3, COLOR_WHITE,   COLOR_GREEN);
	init_pair(4, COLOR_WHITE,     COLOR_RED);
	init_pair(5, COLOR_WHITE,    COLOR_BLUE);

	// Centeral placement of window
	starty1 = starty2 = starty3 = starty4 = getStartY(rows, HEIGHT, 8);
	// Offset by 45 for optimal
	// Lowest you can do is 45
	// Highest you can do is 250
	startx1 = getStartX(cols, WIDTH, 55); 
	startx2 = getStartX(cols, WIDTH, 100);
	startx3 = getStartX(cols, WIDTH, 145);
	startx4 = getStartX(cols, WIDTH, 190);	

	// Pair one with foreground and background
	attron(COLOR_PAIR(1));

	//Putting in the new window
	refresh();
	dWin = createNewWin(HEIGHT, WIDTH, starty1, startx1);
	aWin = createNewWin(HEIGHT, WIDTH, starty2, startx2);
	mWin = createNewWin(HEIGHT, WIDTH, starty3, startx3);
    iWin = createNewWin(HEIGHT, WIDTH, starty4, startx4);

	// Apply color pairs to each window
    wbkgd(dWin, COLOR_PAIR(5));
    wbkgd(aWin, COLOR_PAIR(2));
    wbkgd(mWin, COLOR_PAIR(3));
    wbkgd(iWin, COLOR_PAIR(4));
	attron(COLOR_PAIR(1));
    // Print text to screen
    // Top of screen and middle of screen
	mvprintw(0, (cols - strlen(msg)) / 2, "%s", msg);
	// Print exit hint at bottom
	mvprintw(rows - 1, (cols - strlen(exitHint)) / 2, "%s", exitHint);
	// Messages above windows, mvw print
	mvwprintw(dWin, 0, 2, "DIALOG");
	mvwprintw(aWin, 0, 2, "AREA");
	mvwprintw(mWin, 0, 2, "MOVEMENT");
	mvwprintw(iWin, 0, 2, "INVENTORY");
	// Refresh after apply color and text
 	wrefresh(dWin);
    wrefresh(aWin);
    wrefresh(mWin);
    wrefresh(iWin);

	// User input
	while((ch = getch()) != 'q') {	
		char userIn[100];
		/**
		 * Loop through until q, store outputs of getCommand in an array
		 * Once we will increment the array if the command is successful
		 * To save the game we will output the array to a file
		*/
		switch(ch) {	
			case 'd': // dialog
				mvwprintw(dWin, 1, 1, "YOU WAKE UP IN A GOLDEN FIELD, ON TOP OF "
				"A SMALL HILL, WITH AN OAK TREE AND THREE PATHS. EACH GOING NORTH, SOUTH "
				"AND WEST...\n");
				wrefresh(dWin);
				break;
			case 'a': // area
				mvwprintw(aWin, 1, 1, "YOU MAY GO, NORTH, SOUTH, OR WEST...\n");
				mvwprintw(aWin, 2, 1, "YOU ARE CURRENTLY FACING NORTH...\n");
				wrefresh(aWin);
				break;
			case 'm': // movement
				// Will list the moves you have made until the window is full,
				// Once it is, it will then respawn the window blank and ready
				// To display new commands
				mvwprintw(mWin, 1, 1, "AWAITING COMMAND...\n");
				wrefresh(mWin);
				getCommand(userIn, mWin);
				break;
			case 'i': // inventory
				printInventory(iWin, inventory, inventoryNumCounter);
				wrefresh(iWin);
				break;	
			case 'r': // refresh
			 	wrefresh(dWin);
   				wrefresh(aWin);
    			wrefresh(mWin);
    			wrefresh(iWin);
				refresh();
				break;
		}
	}
	// Wait for user input and endwin
	refresh();
	endwin();
	
	return 0;
}

// Print and upkeep inventory
/**
 * Inventory encoding:
 * 1 = keys
 * 2 = bread
 * 3 = sword
 * 4 = coins
 * 5 = ...
*/
void printInventory(WINDOW* smallWin, int inventory[], int numOfItems){
	for(int i = 0; i < numOfItems; i++) {
		wrefresh(smallWin);

		if(inventory[i] == 0){ // Nothing
			mvwprintw(smallWin, 1, 1, "NO ITEMS YET...\n");
			wrefresh(smallWin);
		}
		if(inventory[i] == 1){ // key
			mvwprintw(smallWin, 1, 1, "YOU HAVE A KEY\n");
			wrefresh(smallWin);
		}
		if(inventory[i] == 2){ // bread
			mvwprintw(smallWin, 2, 1, "YOU BREAD\n");
			wrefresh(smallWin);
		}
	}
}

// Get command function for 
void getCommand(char* userIn, WINDOW* smallWin){
	// Return an int based on string input
	echo();
	wgetstr(smallWin, userIn);
	if(strcmp(userIn, "forward") == 0){ // Forward
		wrefresh(smallWin);
		mvwprintw(smallWin, 1, 1, "YOU MOVED FORWARD\n");
		wrefresh(smallWin);
	} else { // Command Not found
		wrefresh(smallWin);
		mvwprintw(smallWin, 1, 1, "COMMAND NOT FOUND!\n");
		wrefresh(smallWin);
	}
	noecho();
}

// Helper functions
WINDOW* createNewWin(int height, int width, int starty, int startx){	
	WINDOW* localWin;

	localWin = newwin(height, width, starty, startx);
	box(localWin, 0 , 0);
	// Refresh the window
	wrefresh(localWin);
	return localWin;
}



void destroyWin(WINDOW* localWin){	
	wborder(localWin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(localWin);
	delwin(localWin);
}

float getStartY(int rows, int height, float position){
	return (rows - height) - position;
}

float getStartX(int cols, int width, float position){
	return (cols - width) - (cols - position);
}

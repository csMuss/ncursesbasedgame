// ncurses.h includes stdio.h
#include <ncurses.h> 
#include <string.h>

#define NUMWINDOWS 4

WINDOW* createNewWin(int height, int width, int starty, int startx);
void destroyWin(WINDOW* localWin);
float getStartY(int rows, int height, float position);
float getStartX(int cols, int width, float position);

int main(void){

	char msg[] = "BATTLE OF BOMROCK";
	// Variables for getmaxyx
	int rows, cols;

	// Make a smaller window
	WINDOW* smallWin1;
	WINDOW* smallWin2;
	WINDOW* smallWin3;
    WINDOW* smallWin4;

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
	smallWin1 = createNewWin(HEIGHT, WIDTH, starty1, startx1);
	smallWin2 = createNewWin(HEIGHT, WIDTH, starty2, startx2);
	smallWin3 = createNewWin(HEIGHT, WIDTH, starty3, startx3);
    smallWin4 = createNewWin(HEIGHT, WIDTH, starty4, startx4);

	// Apply color pairs to each window
    wbkgd(smallWin1, COLOR_PAIR(5));
    wbkgd(smallWin2, COLOR_PAIR(2));
    wbkgd(smallWin3, COLOR_PAIR(3));
    wbkgd(smallWin4, COLOR_PAIR(4));

    // Refresh each window to apply the color
    wrefresh(smallWin1);
    wrefresh(smallWin2);
    wrefresh(smallWin3);
    wrefresh(smallWin4);

	attron(COLOR_PAIR(1));
    // Print text to screen
    // Top of screen and middle of screen
	mvprintw(0, (cols - strlen(msg)) / 2, "%s", msg);
	
	// User input
	while((ch = getch()) != 'q') {	
		switch(ch) {	
			case 'w': // up
				break;
			case 's': // down
				break;
			case 'a': // left
				break;
			case 'd': // right
				break;	
			case 't': // change string
				char msg1[] = "CHANGED TEXT!!!!";
				mvprintw(0, (cols - strlen(msg1)) / 2, "%s", msg1);
				break;
			case 'r': // refresh
				break;
		}
	}
	// Wait for user input and endwin
	refresh();
	attroff(COLOR_PAIR(1));
	getch();
	endwin();
	
	return 0;
}

// Helper function
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

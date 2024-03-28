#include <ncurses.h> /* ncurses.h includes stdio.h */
#include <string.h>

#define WIDTH 40
#define HEIGHT 38

WINDOW* createNewWin(int height, int width, int starty, int startx);
void destroyWin(WINDOW* localWin);
float getStartY(int rows, float position);
float getStartX(int cols, float position);

int main(void){

	char msg[] = "SAMPLE TEXT";
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
	// Making colorpares
	// Pair one with foreground and background
    start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	// Get terminal variables
	getmaxyx(stdscr, rows, cols);

	// Setting color of main window
	wbkgd(stdscr, COLOR_PAIR(1));
	// Centeral placement of window
	starty1 = starty2 = starty3 = starty4 = getStartY(rows, 8);
	
	startx1 = getStartX(cols, 48);
	startx2 = getStartX(cols, 3.1);
	startx3 = getStartX(cols, 1.6);
	startx4 = getStartX(cols, 1.1);	

	// Pair one with foreground and background
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	attron(COLOR_PAIR(1));

	//Putting in the new window
	refresh();
	smallWin1 = createNewWin(HEIGHT, WIDTH, starty1, startx1);
	smallWin2 = createNewWin(HEIGHT, WIDTH, starty2, startx2);
	smallWin3 = createNewWin(HEIGHT, WIDTH, starty3, startx3);
    smallWin4 = createNewWin(HEIGHT, WIDTH, starty4, startx4);

	attron(COLOR_PAIR(1));
    // Print text to screen
    // Top of screen and middle of screen
    mvprintw(0, (cols - strlen(msg)) / 2.1, "%s", msg);
	
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

float getStartY(int rows, float position){
	return (rows - HEIGHT) / position;
}

float getStartX(int cols, float position){
	return (cols - WIDTH) / position;
}


#include <ncurses.h> /* ncurses.h includes stdio.h */
#include <string.h>

WINDOW* createNewWin(int height, int width, int starty, int startx);
void destroyWin(WINDOW *local_win);

int main(void){

	char msg[] = "SAMPLE TEXT";
	// Variables for getmaxyx
	int rows, cols;
	
    // Make a smaller window
    WINDOW* smallWin;
    int startx, starty, width, height;
    // Character input for the user to interact with the program
    int ch;
	
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
	// Variables for smaller window
	height = 30;
	width = 30;

	// Setting color of main window
	wbkgd(stdscr, COLOR_PAIR(1));
	// Centeral placement of window
	starty = (rows - height) / 2;
	startx = (cols - width) / 2;
	
	// Pair one with foreground and background
	init_pair(1, COLOR_WHITE, COLOR_BLUE);
	attron(COLOR_PAIR(1));

	//Putting in the new window
	refresh();
	smallWin = createNewWin(height, width, starty, startx);
	attron(COLOR_PAIR(1));
    // Print text to screen
    // Top of screen and middle of screen
    mvprintw(0, (cols - strlen(msg)) / 2, "%s", msg);
	
	// User input
	while((ch = getch()) != 'q')
	{	switch(ch)
		{	
			case 'a':
				if(startx > 0){
					destroyWin(smallWin);
					smallWin = createNewWin(height, width, starty, --startx);
				}
				break;
			case 'd':
				if(startx < cols - 1){
					destroyWin(smallWin);
					smallWin = createNewWin(height, width, starty, ++startx);
				}
				break;
			case 'w':
				if(starty > 0){
					destroyWin(smallWin);
					smallWin = createNewWin(height, width, --starty, startx);
				}
				break;
			case 's':
				if(starty < rows - 1){
					destroyWin(smallWin);
					smallWin = createNewWin(height, width, ++starty, startx);
				}
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
WINDOW* createNewWin(int height, int width, int starty, int startx)
{	WINDOW* localWin;

	localWin = newwin(height, width, starty, startx);
	box(localWin, 0 , 0);
	// Refresh the window
	wrefresh(localWin);
	return localWin;
}



void destroyWin(WINDOW* localWin)
{	
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

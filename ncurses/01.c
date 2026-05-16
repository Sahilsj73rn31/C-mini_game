#include <stdio.h>
#include <ncurses/ncurses.h>

int main(int argc, char **argv) {
  
   /* 

   // Initialize ncurses
    //sets out memory and clears the screen
    initscr();

    int  x,y;
    x = y = 10;
    move(y,x);

    printw("Hello World");

    refresh();
    //Refreshes the screen to match memory

    int c = getch();
    //Waits for user input, returns int value of that key
    clear();

    refresh();

    mvprintw(0,0, "%d", c);

    refresh();


    getch();

    endwin();
    //Deallocates memory and ends ncurses mode

    return 0;
    */

/*-----------------------------------------------*/

 /*
    initscr();

    cbreak();
    //Line buffering disabled. pass on everything

    //raw();
    //Line buffering disabled. pass on everything, but Ctrl-C and Ctrl-Z

    noecho();
    //Disables echo of input characters

    int height, width, starty, startx;
    height = 10;
    width = 20;
    starty = startx = 10;

    WINDOW * win = newwin(height, width, starty, startx);

    refresh();

    char b = 'g';

    // box(win , (int)b,103);
    // wborder(win,left,right,top,bottom,tl, tr, bl, br);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    mvwprintw(win, 1, 1, "This is a box");

    wrefresh(win);


    int c = getch();
            getch();

    endwin();
    */

/*-----------------------------------------------*/
    
    /*
    initscr();

    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if(!has_colors())
    {
        printw("Your terminal does not support color\n");
        getch();
        return -1;
    }
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);

    if(can_change_color())
    {
        printw("Your terminal can change colors\n");
        init_color(COLOR_RED, 1000, 0, 0);
    }


    
    attron(COLOR_PAIR(1));
    printw("This is red text");
    attroff(COLOR_PAIR(1));
  
  
    getch();
  
    endwin();



    /*
    A_NORMAL
    A_STANDOUT
    A_UNDERLINE
    A_REVERSE
    A_BLINK
    A_DIM
    A_BOLD
    A_PROTECT
    A_INVIS
    A_ALTCHARSET
    A_CHARTEXT
    A_COLOR
    */

   
   /*
   COLOR_PAIR(n)
   COLOR_BLACK     0
   COLOR_RED       1
   COLOR_GREEN     2
   COLOR_YELLOW    3
   COLOR_BLUE      4
   COLOR_MAGENTA   5
   COLOR_CYAN      6
   COLOR_WHITE     7
   */


/*-----------------------------------------------*/
   
    /*
    initscr(); 

    noecho();
    cbreak();

    int y, x, yBeg, xBeg, yMax, xMax;

    WINDOW * win = newwin(10, 20, 5, 5);

    getyx(stdscr, y, x);
    getbegyx(win, yBeg, xBeg);
    getmaxyx(stdscr, yMax, xMax);

    mvprintw(yMax/2,xMax/2, "%d %d\n",yBeg,xBeg);

    printw("%d %d %d %d %d %d", y, x, yBeg, xBeg, yMax, xMax);


    //make sure program waits before exiting.
    getch();
    endwin();
    */

/*-------------------------------------------*/    
    /*
    initscr();

    noecho();
    cbreak();

    //get screen size
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    //create a window for input
    WINDOW * input = newwin(3, xMax-2, yMax-4, 5);
    box(input, 0, 0);
    refresh();
    wrefresh(input);

    keypad(input, TRUE);


    int c = wgetch(input);
    if(c == KEY_UP)
    {
        mvprintw(1,1, "You pressed KEY_UP");
        wrefresh(input);
    }

    //make sure program waits before exiting.
    getch();

    endwin();
    */

/*-------------------------------------------*/    

    initscr();

    

    endwin();

    return 0;
}


#include<stdio.h>
#include<ncurses/ncurses.h>

int main(int argc, char **argv){

    initscr();

    int y = 20;
    int x = 1;

    int ballX = 19;
    int ballY = 19;

    int ballDirX = 1;
    int ballDirY = 1;

    int paddleHeight = 4;
    
    cbreak();
    noecho();
    
    int yMax, xMax;
    getmaxyx(stdscr ,yMax, xMax);
    
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    
    while(1)
    {
        int i = 0;
        int ch = getch();
        
        clear();
        
        // move ball
        ballX += ballDirX;
        ballY += ballDirY;

        
        if(ballY <= 0 || ballY >= yMax-1){
            ballDirY *= -1;
        }
        if(ballX <= 0 || ballX >= xMax-1){
            ballDirX *= -1;
        }
        
        mvprintw(ballY, ballX, "o");
        mvprintw(0,0,"%d", ch);
        

        // draw paddle
        while(i<paddleHeight){
            mvprintw(y+i,x,"|");
            i++;
        }

        // move paddle
            if(ch == 'w' && y>0){
                y--;
            }
            if(ch == 's' && y+3<yMax-1){
                y++;
            }
            if(ch == 'a' && x>0){
                x--;
            }
            if(ch == 'd' && x<xMax-1){
                x++;
            }

            // quit game
            if(ch == 'q'){
                break;
            }


            // check for collision with paddle
            if (x == ballX && y == ballY){
                ballDirX *= -1;
            }
    

            napms(30);
            refresh();

    }
    
   

    endwin();

    return 0;
}
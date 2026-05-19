#include<stdio.h>
#include<ncurses/ncurses.h>

int main(int argc, char **argv){

    initscr();

    //Border margins
    int leftMargin = 6;
    int rightMargin = 6;
    int topMargin = 7;
    int bottomMargin = 7;

    // player paddle position
    int y = 20;
    int x = leftMargin+1;

    // ball position
    int ballX = 19;
    int ballY = 19;

    // ball direction
    int ballDirX = 1;
    int ballDirY = 1;

    int paddleHeight = 4;

    // get screen size
    int yMax, xMax;
    getmaxyx(stdscr ,yMax, xMax);

    //AI paddle position
    int y0 = 20;
    int x0 = xMax-rightMargin-1;

    //track of frames
    int frameCounter = 0;

    int aiSpeed;
    

    int selected =1;

    cbreak();
    noecho();
    
    
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    // menu
    while(1){
        clear();
        mvprintw(yMax/2-2, xMax/2-10, "Select AI Difficulty:");
        mvprintw(yMax/2, xMax/2-10, "1. EASY");
        mvprintw(yMax/2+1, xMax/2-10, "2. MEDIUM");
        mvprintw(yMax/2+2, xMax/2-10, "3. HARD");
        mvprintw(yMax/2+3, xMax/2-10,"4.GODLY");
        refresh();

        int ch = getch();
        if(ch == '1'){
            aiSpeed = 8;
            break;
        }
        if(ch == '2'){
            aiSpeed = 5;
            break;
        }
        if(ch == '3'){
            aiSpeed = 3;
            break;
        }
        if(ch == '4'){
            aiSpeed = 2;
            break;
        }
    }
    
    
    while(1)
    {
        int i = 0;
        int ch = getch();
        
        clear();

        frameCounter++;
        
        //Bondary
        for(i=leftMargin; i< xMax-rightMargin; i++){
            mvprintw(topMargin, i, "-");
            mvprintw(yMax-bottomMargin, i, "-");
        }
        for(i=topMargin; i< yMax-bottomMargin; i++){
            mvprintw(i, leftMargin, "|");
            mvprintw(i, xMax-rightMargin, "|");
        }

        // move ball
        ballX += ballDirX;
        ballY += ballDirY;

        //wall collision
        if(ballY <= topMargin || ballY >= yMax-bottomMargin-1){
            ballDirY *= -1;
        }
        if(ballX <= leftMargin || ballX >= xMax-rightMargin-1){
            ballDirX *= -1;
        }
        
        mvprintw(ballY, ballX, "o");
     
        // draw paddle
       for(int i = 0; i < paddleHeight; i++){
            mvprintw(y+i, x, "|");
}

        // move paddle
            if(ch == 'w' && y>topMargin){
                y--;
            }
            if(ch == 's' && y+paddleHeight<yMax-bottomMargin){
                y++;
            }

            // quit game
            if(ch == 'q'){
                break;
            }


            // check for collision with paddle
            if (x+1 == ballX && y <= ballY && y + paddleHeight >= ballY) {
                ballDirX *= -1;

                // Move the ball to the right of the paddle to prevent it from getting stuck

                ballX = x+2;

            }

        //AI paddle 
        for (i=0; i<paddleHeight; i++){
            mvprintw(y0+i,x0,"|");
        }    
            // move AI paddle
            if(ballX < x0-1){
                if(frameCounter %aiSpeed ==0){
                    if(ballY>y0 && y0 + paddleHeight < yMax-bottomMargin-1){
                        y0++;
                    }
                    if(ballY<y0 && y0 > topMargin){
                        y0--;
                    }
                }
            }

        //AI collision
        if(ballX==x0-1 && y0 <= ballY && y0 + paddleHeight >= ballY){
            ballDirX *= -1;
            ballX = x0-2;
        }

    

          napms(20);
            refresh();

    }
    
   

    endwin();

    return 0;
}
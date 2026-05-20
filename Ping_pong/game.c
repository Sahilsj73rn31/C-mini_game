#include<stdio.h>
#include<ncurses/ncurses.h>

int main(int argc, char **argv){

    initscr();

    int paddleHeight = 4;

    int yMax, xMax;
    getmaxyx(stdscr ,yMax, xMax);

    //Border margins
    int leftMargin = 6;
    int rightMargin = 6;
    int topMargin = 7;
    int bottomMargin = 7;

    // player paddle position
    int y = yMax -(topMargin + bottomMargin)/2 - paddleHeight/2;
    int x = leftMargin+1;

    // ball position
    int ballX = 19;
    int ballY = 19;

    // ball direction
    int ballDirX = 1;
    int ballDirY = 1;


    // get screen size

    //AI paddle position
    int y0 = yMax -(topMargin + bottomMargin)/2 - paddleHeight/2;
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
        drawMenu(yMax, xMax);
        refresh();

        int ch = getch();
        
        handleMenuInput(ch, &aiSpeed);
    }
    
    
    while(1)
    {
        int i = 0;
        int ch = getch();
        
        clear();

        frameCounter++;
        
        //Bondary
        drawBoundary(leftMargin, rightMargin, topMargin, bottomMargin, xMax, yMax);

        // move ball
        ballMovement(ballX, ballY, ballDirX, ballDirY);

        //wall collision
        wallCollision(ballX, ballY, ballDirX, ballDirY, leftMargin, rightMargin, topMargin, bottomMargin, xMax, yMax);
        
        //draws ball
        drawBall(ballX, ballY);
     
        // draw paddle for user
        drawPaddle(y, x, paddleHeight);

        // move paddle
        userPaddleMovement(ch, &y, topMargin, bottomMargin, yMax, paddleHeight);

        // check for collision with paddle
        ballCollisionWithUserPaddle(ballX, ballY, ballDirX, ballDirY, x, y, paddleHeight);

        //AI paddle 
        drawPaddle(y0, x0, paddleHeight);

        // move AI paddle
        aiPaddleMovement(ballX, ballY, ballDirX, ballDirY, x0, y0, paddleHeight, topMargin, bottomMargin, yMax, frameCounter, aiSpeed);

        //AI collision
        aiPaddleCollision(ballX, ballY, ballDirX, ballDirY, x0, y0, paddleHeight);

    

        updateFrame(frameCounter);

    }
    
    endwin();

    return 0;
}




void drawPaddle(int y, int x , int paddleHeight){

    int i;

    for(i=0 ; i<paddleHeight ; i++){
        mvprintw(y+i, x, "|");
    }
}

void drawBall(int ballX, int ballY){

    mvprintw(ballY, ballX, "o");

}

void drawBoundary(int leftMargin, int rightMargin, int topMargin, int bottomMargin, int xMax, int yMax){

    int i;

    for(i=leftMargin; i< xMax-rightMargin; i++){
        mvprintw(topMargin, i, "-");
        mvprintw(yMax-bottomMargin, i, "-");
    }
    for(i=topMargin; i< yMax-bottomMargin; i++){
        mvprintw(i, leftMargin, "|");
        mvprintw(i, xMax-rightMargin, "|");
    }
}

void ballMovement(int ballX, int ballY, int ballDirX, int ballDirY){

    ballX += ballDirX;
    ballY += ballDirY;
    
}

void wallCollision(int ballX, int ballY, int ballDirX, int ballDirY, int leftMargin, int rightMargin, int topMargin, int bottomMargin, int xMax, int yMax){
    if(ballY <= topMargin || ballY >= yMax-bottomMargin-1){
        ballDirY *= -1;
    }
    if(ballX <= leftMargin || ballX >= xMax-rightMargin-1){
        ballDirX *= -1;
    }
}

void ballCollisionWithUserPaddle(int ballX, int ballY, int ballDirX, int ballDirY, int x, int y, int paddleHeight){
    // check for collision with paddle
    if (x+1 == ballX && y <= ballY && y + paddleHeight >= ballY) {
        ballDirX *= -1;

        // Move the ball to the right of the paddle to prevent it from getting stuck

        ballX = x+2;

    }
}

void aiPaddleMovement(int ballX, int ballY, int ballDirX, int ballDirY, int x0, int y0, int paddleHeight, int topMargin, int bottomMargin, int yMax, int frameCounter, int aiSpeed){
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
}

void aiPaddleCollision(int ballX, int ballY, int ballDirX, int ballDirY, int x0, int y0, int paddleHeight){
    //AI collision
    if(ballX==x0-1 && y0 <= ballY && y0 + paddleHeight >= ballY){
        ballDirX *= -1;
        ballX = x0-2;
    }
}

void drawMenu(int yMax, int xMax){
    mvprintw(yMax/2-2, xMax/2-10, "Select AI Difficulty:");
    mvprintw(yMax/2, xMax/2-10, "1. EASY");
    mvprintw(yMax/2+1, xMax/2-10, "2. MEDIUM");
    mvprintw(yMax/2+2, xMax/2-10, "3. HARD");
    mvprintw(yMax/2+3, xMax/2-10,"4.GODLY");
}

void handleMenuInput(int ch, int *aiSpeed){
    if(ch == '1'){
        *aiSpeed = 8;
    }
    if(ch == '2'){
        *aiSpeed = 5;
    }
    if(ch == '3'){
        *aiSpeed = 3;
    }
    if(ch == '4'){
        *aiSpeed = 2;
    }
}

void userPaddleMovement(int ch, int *y, int topMargin, int bottomMargin, int yMax, int paddleHeight){
    if(ch == 'w' && *y>topMargin){
        (*y)--;
    }
    if(ch == 's' && *y+paddleHeight<yMax-bottomMargin){
        (*y)++;
    }
}

void quitGame(int ch, int *running){
    if(ch == 'q'){
        *running = 0;
    }
}

void updateFrame(int frameCounter){
    napms(30);
    refresh();
}

#include<stdio.h>
#include<ncurses/ncurses.h>


//function prototypes
void drawPaddle(int y, int x , int paddleHeight);
void drawBall(int ballX, int ballY);
void drawBoundary(int leftMargin, int rightMargin, int topMargin, int bottomWall, int xMax, int yMax);
void ballMovement(int *ballX, int *ballY, int ballDirX, int ballDirY);
void wallCollision(int *ballX, int *ballY, int *ballDirX, int *ballDirY, int topMargin, int bottomWall);
void ballCollisionWithUserPaddle(int *ballX, int *ballY, int *ballDirX, int x, int y, int paddleHeight);
void aiPaddleMovement(int *ballX, int *ballY, int x0, int *y0, int paddleHeight, int topMargin, int bottomWall, int frameCounter, int aiSpeed);
void aiPaddleCollision(int *ballX, int *ballY, int *ballDirX, int x0, int y0, int paddleHeight);
void drawMenu(int yMax, int xMax);
void handleMenuInput(int ch, int *aiSpeed, int *menuRunning);
void userPaddleMovement(int ch, int *y, int topMargin, int bottomWall, int paddleHeight);
void quitGame(int ch, int *running);
void userNameFun(char *userName,int yMax, int xMax, int *userNameInput);
void scoring(int *ballX,int *ballY,int *ballDirX, int *ballDirY, int *userScore,int leftMargin,int rightMargin, int xMax,int yMax,int *aiScore, char *userName);


//Main function

int main(int argc, char **argv){

    initscr();

    curs_set(0);
    
    int paddleHeight = 4;
    
    // get screen size
    int yMax, xMax;
    getmaxyx(stdscr ,yMax, xMax);
    
    //Border margins
    int leftMargin = 26;
    int rightMargin = 26;
    int topMargin = 3;
    int bottomMargin = 3;
    
    //for bottom wall
    int bottomWall = yMax - bottomMargin -2;

    // player paddle position
    int y = yMax/2 - paddleHeight/2;
    int x = leftMargin+1;
    
    // ball position
    int ballX = 30;
    int ballY = 20;
    
    // ball direction
    int ballDirX = 1;
    int ballDirY = 1;
    
    //AI paddle position
    int y0 = yMax/2 - paddleHeight/2;
    int x0 = xMax-rightMargin-1;
    
    //track of frames
    int frameCounter = 0;
    
    // AI difficulty
    int aiSpeed;
    
    // menu running flag
    int menuRunning = 1;
    
    //game Running
    int running = 1;

    //scoring
    int userScore = 0;
    int aiScore = 0;

    //user Name
    char userName[20];
    int userNameInput = 1;
    
    cbreak();
    noecho();
    
    
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);

    leaveok(stdscr, TRUE);

    set_escdelay(25);

    //user Name Input
    while(userNameInput){
        clear();
        userNameFun(userName, yMax,xMax, &userNameInput);
        refresh();

    }
    
    // menu
    while(menuRunning){
        clear();
        drawMenu(yMax, xMax);
        refresh();
        
        int ch = getch();
        
        handleMenuInput(ch, &aiSpeed, &menuRunning);
    }
    
    nodelay(stdscr , TRUE);
    
    timeout(16);

    //Bondary(outside for better fps)
    drawBoundary(leftMargin, rightMargin, topMargin, bottomWall, xMax, yMax);
    
    while(running)
    {
        int ch = getch();
        
        clear();
        
        frameCounter++;

        //wall collision
        wallCollision(&ballX, &ballY, &ballDirX, &ballDirY, topMargin, bottomWall);
        
        // move ball
        ballMovement(&ballX, &ballY, ballDirX, ballDirY);

        // move paddle
        userPaddleMovement(ch, &y, topMargin, bottomWall,paddleHeight);
        
        // check for collision with paddle
        ballCollisionWithUserPaddle(&ballX, &ballY, &ballDirX, x, y, paddleHeight);

        // move AI paddle
        aiPaddleMovement(&ballX, &ballY, x0, &y0, paddleHeight, topMargin, bottomWall, frameCounter, aiSpeed);
        
        //AI collision
        aiPaddleCollision(&ballX, &ballY, &ballDirX, x0, y0, paddleHeight);

        //scoring
        scoring(&ballX,&ballY,&ballDirX, &ballDirY, &userScore,leftMargin, rightMargin, xMax,yMax, &aiScore, userName);
        
        
        //draws ball
        drawBall(ballX, ballY);
        
        // draw paddle for user
        drawPaddle(y, x, paddleHeight);
        
        //AI paddle 
        drawPaddle(y0, x0, paddleHeight);
        
        // quit game
        quitGame(ch, &running);
        

        refresh();
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

void drawBoundary(int leftMargin, int rightMargin, int topMargin, int bottomWall, int xMax, int yMax){

    int i;

    for(i=leftMargin; i< xMax-rightMargin; i++){
        mvprintw(topMargin, i, "-");
        mvprintw(bottomWall, i, "-");
    }
    for(i=topMargin; i< bottomWall; i++){
        mvprintw(i, leftMargin, "|");
        mvprintw(i, xMax-rightMargin, "|");
    }
}

void ballMovement(int *ballX, int *ballY, int ballDirX, int ballDirY){

    *ballX += ballDirX;
    *ballY += ballDirY;
    
}

void wallCollision(int *ballX, int *ballY, int *ballDirX, int *ballDirY, int topMargin, int bottomWall){
    if(*ballY <= topMargin +1 || *ballY >= bottomWall -1){
        *ballDirY *= -1;
    }
}

void ballCollisionWithUserPaddle(int *ballX, int *ballY, int *ballDirX, int x, int y, int paddleHeight){
    // check for collision with paddle
    if (x+1 == *ballX && y <= *ballY && y + paddleHeight -1 >= *ballY) {
        *ballDirX *= -1;

        // Move the ball to the right of the paddle to prevent it from getting stuck

        *ballX = x+2;

    }
}

void aiPaddleMovement(int *ballX, int *ballY,int x0, int *y0, int paddleHeight, int topMargin, int bottomWall, int frameCounter, int aiSpeed){
    // move AI paddle
    if(*ballX < x0-1){
        if(frameCounter %aiSpeed ==0){
            if(*ballY>*y0 && *y0 + paddleHeight < bottomWall){
                (*y0)++;
            }
            if(*ballY<*y0 && *y0 > topMargin){
                (*y0)--;
            }
        }
    }
}

void aiPaddleCollision(int *ballX, int *ballY, int *ballDirX, int x0, int y0, int paddleHeight){
    //AI collision
    if(*ballX==x0-1 && y0 <= *ballY && y0 + paddleHeight -1 >= *ballY){
        *ballDirX *= -1;
        *ballX = x0-2;
    }
}

void drawMenu(int yMax, int xMax){
    mvprintw(yMax/2-2, xMax/2-10, "Select AI Difficulty:");
    mvprintw(yMax/2, xMax/2-10, "1. EASY");
    mvprintw(yMax/2+1, xMax/2-10, "2. MEDIUM");
    mvprintw(yMax/2+2, xMax/2-10, "3. HARD");
    mvprintw(yMax/2+3, xMax/2-10,"4.GODLY");
}

void handleMenuInput(int ch, int *aiSpeed, int *menuRunning){
    if(ch == '1'){
        *aiSpeed = 5;
        *menuRunning = 0;
    }
    if(ch == '2'){
        *aiSpeed = 3;
        *menuRunning = 0;
    }
    if(ch == '3'){
        *aiSpeed = 2;
        *menuRunning = 0;
    }
    if(ch == '4'){
        *aiSpeed = 1;
        *menuRunning = 0;
    }
}

void userPaddleMovement(int ch, int *y, int topMargin, int bottomWall, int paddleHeight){
    if(ch == 'w' && *y>topMargin){
        (*y)--;
    }
    if(ch == 's' && *y+paddleHeight < bottomWall ){
        (*y)++;
    }
}

void quitGame(int ch, int *running){
    if(ch == 'q'){
        *running = 0;
    }
}

void userNameFun(char *userName ,int yMax, int xMax ,int *userNameInput){
    mvprintw(yMax/2 ,(xMax/2)-12 ,"Please enter your name:");
    echo();
    mvgetnstr((yMax/2) +1 , xMax/2,userName,19);
    noecho();
    *userNameInput = 0;
}

void scoring(int *ballX,int *ballY,int *ballDirX, int *ballDirY, int *userScore,int leftMargin, int rightMargin,  int xMax,int yMax, int *aiScore, char *userName){
    if(*ballX >= xMax - rightMargin){

        (*userScore)++;

        *ballX =xMax/2;
        *ballY =yMax/2;

        *ballDirX = -1;
        *ballDirY = 1;

    }
    if(*ballX <= leftMargin){
        
        (*aiScore)++;

        *ballX =xMax/2;
        *ballY =yMax/2;

        *ballDirX = -1;
        *ballDirY = 1;

    }


    mvprintw(1,(xMax/2)-10,"%s:%d",userName,*userScore);
    
    mvprintw(1,(xMax/2)-1,"vs");
    
    mvprintw(1,(xMax/2)+8,"AI:%d",*aiScore);
}

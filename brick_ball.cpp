#include <graphics.h>
#include <conio.h>
#define BRICK_W 50
#define BRICK_H 20

#define PADDLE_W 70
#define PADDLE_H 20
#define PADDLE_INIT_X 205
#define PADDLE_INIT_Y 280

#define NUM_ROWS 3
#define NUM_COLS 5

#define X_MARGIN 20
#define Y_MARGIN 10
#define X_GAP 20
#define Y_GAP 10
#define BALL_R 8
#define INIT_BALL_X 240
#define INIT_BALL_Y 272

class Ball
{
public:
    int radius,x,y;
    Ball()
    {
        x=INIT_BALL_X;
        y=INIT_BALL_Y;
        radius=BALL_R;
    }
    void draw()
    {
        circle(x, y,radius);
    }
    void erase()
    {
        int previousColor = getcolor();
        setcolor(0);
        circle(x, y, radius);
        setcolor(previousColor);
    }
};

class Paddle
{
public:
    int x, y, w, h;

    Paddle()
    {
        x = PADDLE_INIT_X;
        y = PADDLE_INIT_Y;
        w = PADDLE_W;
        h = PADDLE_H;
    }

    void draw()
    {
        setfillstyle(SOLID_FILL, 5);
        bar(x, y, x+w, y+h);
    }

    void erase()
    {
        setfillstyle(SOLID_FILL, 0);
        bar(x, y, x+w, y+h);
    }

    void moveLeft()
    {
        x -= 10;
    }

    void moveRight()
    {
        x += 10;
    }
};

class Brick
{
public:
    int x, y, w, h, id;
    bool isDestroyed;

    Brick()
    {
        isDestroyed = false;
        w = BRICK_W;
        h = BRICK_H;
    }

    void initialize(int _id, int _x, int _y)
    {
        id = _id;
        x = _x;
        y = _y;
    }

    void draw()
    {
        rectangle(x, y, x+w, y+h);
    }

    void erase()
    {
        int previousColor = getcolor();
        setcolor(0);
        rectangle(x,y,x+w,y+h);
        setcolor(previousColor);
    }
};

int brickCount = NUM_ROWS * NUM_COLS;
Brick bricks[NUM_ROWS * NUM_COLS];
Paddle paddleObj;
Ball ballObj;

void processInput()
{
    char input ='k';
    if(kbhit())
        {
            input = getch();
            switch(input)
            {
                case 'x':
                    exit(0);
                case 'a':
                    paddleObj.moveLeft();
                    break;
                case 'd':
                    paddleObj.moveRight();
                    break;
            }
        }
}

void drawGame()
{
    int i;
    for (i = 0; i < brickCount; i++)
    {
        bricks[i].draw();
    }
    ballObj.draw();
    paddleObj.draw();
}

void eraseGame()
{
    ballObj.erase();
    paddleObj.erase();
}

int main()
{
    initwindow(480, 320, "Second");

    int row, col;
    int brickID = 0;
    int x, y;
    x = X_MARGIN;
    y = Y_MARGIN;
    for (row = 1; row <= NUM_ROWS; row++)
    {
        for (col = 1; col <= NUM_COLS; col++)
        {
            bricks[brickID].initialize(brickID, x, y);
            brickID++;
            x = x + BRICK_W + X_GAP;
        }
        x = X_MARGIN;
        y = y + BRICK_H + Y_GAP;
    }

    setcolor(2);

    //The following while loop
    //defines the GameLoop

    while(1)
    {
        eraseGame();
        processInput();

        drawGame();
    }

    getch();
}


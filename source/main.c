/*
Breakout Port for 3DS
CalebW
*/

#include "HID.h"
#include "memory.h"
#include "main.h"
#include "utils.h"
#include "draw.h"


int levelold = 1;
int livesold = 3;
int paddle_Xedge = 180;
int paddle_Xedgeold = 180;
int button_press = 0;
int ball_size = 4;
int level = 1;
int lives = 5;
int bricks[BRICKS_VERTICALLY][BRICKS_HORIZONTALLY];
int ballY,ballX,ballYV,ballXVold,ballXV,ballYVold,ballXold,ballYold;



int main(){

    clearscreen(TOP_SCREEN | BOTTOM_SCREEN);
    initscreens();
    drawtitle();
    initscreens();
    setup();
    main_loop();
    return 0;
}

void main_loop(){
    while(1){
            key_press();
            ball_move();
            update_screen();
            if(bricks_remaining() == 0){
                level++;
                lives++;
                draw_fillcircle(ballXold, ballYold, ball_size, 90, 100, 225, TOP_SCREEN);
                setup();
            }
     }
}

void setup(){
    reset_ball();
    reset_bricks();
    update_screen();
}

void reset_paddle(){
    int paddle_Xedge = 180;
    int paddle_Xedgeold = 180;
}

void drawtitle(){
    char x,y = 0;
    for(x = 0;x < 240;x++){
        if(title[x]>0) paintsquares(x, y, title[x]);
    }
    draw_string("Press SELECT to Start", 60, 100 ,255, 255, 255, BOTTOM_SCREEN);
    draw_string("Press Left/Right or Y/A to Move", 60, 110, 255, 255, 255, BOTTOM_SCREEN);
    draw_string("Press X to Pause", 60, 120, 255, 255, 255, BOTTOM_SCREEN);
    draw_string("Press Start to Quit", 60, 130, 255, 255, 255, BOTTOM_SCREEN);
    while(1){
        button_press = read_word(HID);
        if(!(button_press & BUTTON_SELECT)) break;
    }
}


void pause(){
    initscreens();
    char x,y;
    for(x = 0;x < 120;x++)
        paintsquares(x, y, pause_a[x]);
    draw_string("Press X", 120, 120, 255, 255, 255,BOTTOM_SCREEN);
    while(1){
        button_press = read_word(HID);
        if(!(button_press & BUTTON_X)) break;
    }
}

void paintsquares(int x, int y, char color){
    y = x / 20;
    x = x % 20;
    draw_fillrect(x*20,y*20,(x+1)*20-BRICK_GAP,(y+1)*20-BRICK_GAP,colors[color][0],colors[color][1],colors[color][2], TOP_SCREEN);
}


void initscreens(){
    draw_fillrect(0, 0, 320, 240, 90, 100, 225, BOTTOM_SCREEN);
    draw_fillrect(0, 0, 400, 240, 90, 100, 225, TOP_SCREEN);
}

void reset_ball(){
    ballX = 200;
    ballXold = 200;
    ballY = 140;
    ballYold = 140;
    ballXV = -5;
    ballXVold = ballXV;
    ballYV = -7;
    ballYVold = ballYV;
}

void reset_bricks(){
    int y;
    int x; 
    for(y = 0; y < BRICKS_VERTICALLY; y++){
        for(x = 0;x < BRICKS_HORIZONTALLY; x++){
            bricks[y][x] = 3;
        }
    }
}


int bricks_remaining(){

    int count = 0;
    int y;
    int x;
    for(y = 0;y < BRICKS_VERTICALLY; y++){
        for(x = 0;x < BRICKS_HORIZONTALLY; x++){
            if(bricks[y][x] != 0) count++;
        }
    }
    return count;
}


void key_press(){

    button_press = read_word(HID);
    if((!(button_press & BUTTON_LEFT) | !(button_press & BUTTON_Y)) && (paddle_Xedge > 3)){
        paddle_Xedge = paddle_Xedge - 15;
    }
    if((!(button_press & BUTTON_RIGHT) | !(button_press & BUTTON_A)) && (paddle_Xedge < (392 - PADDLE_WIDTH))){
        paddle_Xedge = paddle_Xedge + 15;
    }
    if(!(button_press & BUTTON_START)){
        restart();
    }
    if(!(button_press & BUTTON_X)){
        pause();
        initscreens();
    }
}



void update_screen(){
    //draws the bricks
    int y;
    int x;
    for(y = 0;y < BRICKS_VERTICALLY; y++){
        for(x = 0;x < BRICKS_HORIZONTALLY; x++){
            if(bricks[y][x] == 3){
                draw_fillrect(x*BRICK_WIDTH, y*BRICK_HEIGHT, (x+1)*BRICK_WIDTH-BRICK_GAP, (y+1)*BRICK_HEIGHT-BRICK_GAP, 0, 255, 0, TOP_SCREEN);
            }
            if(bricks[y][x] == 2){
                draw_fillrect(x*BRICK_WIDTH, y*BRICK_HEIGHT, (x+1)*BRICK_WIDTH-BRICK_GAP, (y+1)*BRICK_HEIGHT-BRICK_GAP, 255, 0, 0, TOP_SCREEN);
            }
            if(bricks[y][x] == 1){
                draw_fillrect(x*BRICK_WIDTH, y*BRICK_HEIGHT, (x+1)*BRICK_WIDTH-BRICK_GAP, (y+1)*BRICK_HEIGHT-BRICK_GAP, 90, 100, 225, TOP_SCREEN);
            }
            if(bricks[y][x] == 1){
                bricks[y][x] = 0;
            }
        }
    }
    //draws the paddle

    draw_fillrect(paddle_Xedgeold, PADDLE_Y, paddle_Xedgeold+PADDLE_WIDTH, PADDLE_Y+PADDLE_HEIGHT, 90, 100, 225, TOP_SCREEN);
    draw_fillrect(paddle_Xedge, PADDLE_Y, paddle_Xedge+PADDLE_WIDTH, PADDLE_Y+PADDLE_HEIGHT, 0, 255, 0, TOP_SCREEN);

    //draws ball
        draw_fillcircle(ballXold, ballYold, ball_size, 90, 100, 225, TOP_SCREEN);
        draw_fillcircle(ballX, ballY, ball_size, 255, 255, 255, TOP_SCREEN);


    char var[14];
    char var2[14];

    draw_string("Breakout3DS v.1 - CalebW", 0, 231, 255, 255, 255, BOTTOM_SCREEN);
    draw_string("Lives: ", 0, 0, 255,255,255,BOTTOM_SCREEN);
    itoa(lives, var);
    itoa(livesold, var2);
    draw_string(var2, 50, 0, 90, 100, 225, BOTTOM_SCREEN);
    draw_string(var, 50, 0, 255, 255, 255, BOTTOM_SCREEN);
    draw_string("Level: ", 0, 10, 255, 255, 255, BOTTOM_SCREEN);
    itoa(level, var);
    itoa(levelold,var2);
    draw_string(var2, 50, 10, 90, 100, 225, BOTTOM_SCREEN);
    draw_string(var, 50, 10, 255, 255, 255, BOTTOM_SCREEN);
    draw_string("Paddle X: ", 0, 20, 255, 255, 255, BOTTOM_SCREEN);
    itoa(paddle_Xedge, var);
    itoa(paddle_Xedgeold, var2);
    draw_string(var2, 70, 20, 90, 100, 225, BOTTOM_SCREEN);
    draw_string(var, 70, 20, 255, 255, 255, BOTTOM_SCREEN);
    draw_line(0, 0, 0, 240, 90, 100, 225, TOP_SCREEN | BOTTOM_SCREEN);
    draw_string("Ball XY Velocity:  ,", 0, 30, 255, 255, 255, BOTTOM_SCREEN);
    itoa(ballXV, var);
    itoa(ballXVold, var2);
    draw_string(var2, 135, 30, 90, 100, 225, BOTTOM_SCREEN);
    draw_string(var, 135, 30, 255, 255, 255, BOTTOM_SCREEN);
    itoa(ballYV, var);
    itoa(ballYVold, var2);
    draw_string(var2, 157, 30, 90, 100, 225, BOTTOM_SCREEN);
    draw_string(var, 157, 30, 255, 255, 255, BOTTOM_SCREEN);

    levelold = level;
    livesold = lives;
    ballYold = ballY;
    ballXold = ballX;
    ballXVold = ballXV;
    ballYVold = ballYV;
    paddle_Xedgeold = paddle_Xedge;
    wait(300/level);
}



int ball_overlap(int ballX, int ballY, 
                int area_left, int area_top,
                int area_right, int area_bottom){

    if(ballX >= (area_left-ball_size) && ballX <= (area_right+ball_size)  &&
        ballY >= (area_top-ball_size) && ballY <= (area_bottom+ball_size)){
            return 1;//overlaped
    }
    return 0;//did not overlap
}


void ball_move(){
    //update positions for next frame
    ballX += ballXV;
    ballY += ballYV;


// if the ball is overlapping the paddle rectangle
    if(ballYV > 0) { // only if the ball is moving down
        if(ball_overlap(ballX, ballY,
            paddle_Xedge + (PADDLE_WIDTH*0.0),
            PADDLE_Y - ball_size, paddle_Xedge + (PADDLE_WIDTH*0.25),
            PADDLE_Y + PADDLE_HEIGHT) == 1) {
                ballXV = -7;
                ballYV = -5;
        }
        if(ball_overlap(ballX, ballY,
            paddle_Xedge + (PADDLE_WIDTH*0.25),
            PADDLE_Y - ball_size, paddle_Xedge + (PADDLE_WIDTH*0.5),
            PADDLE_Y + PADDLE_HEIGHT) == 1) {
                ballXV = -5;
                ballYV = -7;
        }
        if(ball_overlap(ballX, ballY,
            paddle_Xedge + (PADDLE_WIDTH*0.5),
            PADDLE_Y - ball_size, paddle_Xedge + (PADDLE_WIDTH*0.75),
            PADDLE_Y + PADDLE_HEIGHT) == 1) {
                ballXV = 5;
                ballYV = -7;
            }
        if(ball_overlap(ballX, ballY,
            paddle_Xedge + (PADDLE_WIDTH*0.75),
            PADDLE_Y - ball_size, paddle_Xedge + (PADDLE_WIDTH*1.0),
            PADDLE_Y + PADDLE_HEIGHT) == 1) {
                ballXV = 7;
                ballYV = -5;
        }
    }

    
    //checks if ball collides with bricks
    int x;
    int y;
    for(y = 0;y < BRICKS_VERTICALLY; y++){
        for(x = 0;x < BRICKS_HORIZONTALLY; x++){
            if(bricks[y][x] != 0){
                if(ball_overlap(ballX, ballY, x*BRICK_WIDTH - ball_size, 
                    y*BRICK_HEIGHT+2, (x+1)*BRICK_WIDTH-BRICK_GAP + ball_size, 
                    (y+1)*BRICK_HEIGHT-BRICK_GAP + ball_size) == 1){
                    //reverses ball direction
                    ballYV = -ballYV;
                    bricks[y][x] = bricks[y][x] - 1;  //gets rid of bricks
                }
            }
        }
    }
    
    //checks if ball collides with screen
    if(ballX > 394 - ball_size){
        ballXV = -ballXV;
    }
    if(ballX < 6 + ball_size){
        ballXV = -ballXV;
    }
    if(ballY < 7 + ball_size){
        ballYV = -ballYV;
    }
    if(ballY > 240 - ball_size){
        lives--;
        if(lives > 0){
            draw_fillcircle(ballXold, ballYold, ball_size, 90, 100, 225, TOP_SCREEN);
            reset_ball();
        }
        else{
           game_over();
        }
    }
}

void game_over(){
    drawgameover();
    lives = 5;
    level = 1;
    initscreens();
    reset_ball();
    reset_bricks();
}


void restart(){
    initscreens();
    drawtitle();
    initscreens();
    setup();
    main_loop();
}


void drawgameover(){
    initscreens();
    char x,y;
    for(x = 0;x < 240;x++)
        paintsquares(x, y, gameover[x]);
    draw_string("Press Select", 120, 120, 255, 255, 255,BOTTOM_SCREEN);
    while(1){
        button_press = read_word(HID);
        if(!(button_press & BUTTON_SELECT)) break;
    }
}


void wait(int t){
    int i = 0;
    int j = 0;
    int z = 0;

    for (i = 0; i < t; i++) {
        for (j = 0; j < t; j++) {
            z = i / 33;
        }
    }

};


#include "player2.h"
#include <stdlib.h> 

void updatePlayer2AI(Player *player2, Ball *ball, int counter) {
    int player2X = player2->x;
    int player2Y = player2->y;
    int ballX = ball->x;
    int ballY = ball->y;

    int deltaX = ballX - player2X;
    int deltaY = ballY - player2Y;

    //the player2 is starting the game
    if(player2->state == CHOOSE_START_STOP){
        if(counter % 60 == 0){
            player2->state = START;
        }
    }


    // Prioritize movement along the axis with the largest difference
    if(player2->state == MOVE || player2->state == STOP){
        player2->state = MOVE;
        
        //player need to move in the x direction
        if ((abs(deltaX) > abs(deltaY)) ) {
            if (deltaX < 0) {
                player2->movement = LEFT_PLAYER;
                player2->direction = LEFTD;
            } else if (deltaX > 0) {
                player2->movement = RIGHT_PLAYER;
                player2->direction = RIGHTD;
            }

            //the player needs to move in the y direction
        } else if (ball ->y  < MAX_Y_P2) {
            if (deltaY < 0) {
                player2->movement = UP_PLAYER;
            } else if (deltaY > 0) {
                player2->movement = DOWN_PLAYER;
            }
        }

        //the ball if on the player 1 side
        else if((ball ->y  > MAX_Y_P2) && (abs(deltaX) > 6)){
            if (deltaX < 0) {
                player2->movement = LEFT_PLAYER;
                player2->direction = LEFTD;
            } else if (deltaX > 0) {
                player2->movement = RIGHT_PLAYER;
                player2->direction = RIGHTD;
            }
        }

        //the player doesn't need to move
        else{
            player2->state = STOP;
        }
    }
    

    
    // Check for collision between player2 and the ball
    // Get the current hit limits of player2
    int x_min, x_max, y_min, y_max;
    get_current_hit_limits(player2, &x_min, &x_max, &y_min, &y_max);

   
    //corrects the position in order to hit the ball
    if((ball->x >= player2X - 10) && (ball-> x <= x_min + 10) && (ballY <= y_max + 100) && (ballY >= y_min)){
            player2->direction = LEFTD;
        }
    if((ball->x >= x_min - 10) && (ball-> x <= x_max + 10)  && (ballY <= y_max + 100) && (ballY >= y_min)){
            player2->direction = RIGHTD;
    }

    // Check if the ball is within the hit limits of player2
    if ((ballX >= x_min + 10 ) && (ballX <= x_max -10) && (ballY >= y_min) && (ballY <= y_max )) {
            // If there is a collision, trigger a hit animation for player2
            player2->state = HIT;

    }



    updatePlayerMovementsTimer(player2, counter);
    
    
}

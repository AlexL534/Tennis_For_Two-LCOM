#include "game.h"
#include "background.h"


//static Game_state game_state = GAME;
static Player *player1;
static Player *player2;
static Ball *ball;
int player1Score = 0;
int player2Score = 0;
static bool canHitAfterServe = false;

static uint32_t *background;

extern int counter;

int (gameLoop)(){
  
  if(loadBackground() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(loadInitialXPMScore() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }
  
  player1 = createPlayer1();
  player2 = createPlayer2();
  ball = createBall();

  if(drawPlayer(player1) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(drawPlayer(player2) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(drawScore(1) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(drawScore(2) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(drawScoreText() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  timer_set_frequency(0, 60);
  if(kbd_subscribe_int(&bit_no) != 0){
    destroyElements();
      return EXIT_FAILURE;
  }
  uint8_t kbc_mask = BIT(bit_no);

  if(timer_subscribe_int(&bit_no) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }
  uint8_t timer_mask = BIT(bit_no);

  if(mouse_subscribe_int(&bit_no) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }
  uint8_t mouse_mask = BIT(bit_no);

  while( (get_scancode() != KBD_ESC_BREAK) && (player1Score < 10) && (player2Score < 10)){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { 
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE:
                  if(msg.m_notify.interrupts & mouse_mask){
                    mouse_ih();
                    mouse_insert_byte();
                    if(get__mouse_byte_index() == 3){
                      mouse_insert_in_packet();
                      mouseHandler();
                      reset_byte_index();
                    }
                    drawMouse();

                 } 		
                 if (msg.m_notify.interrupts & kbc_mask) { 
                       kbc_ih();
                       keyboardHandler();
                 }
                 if(msg.m_notify.interrupts & timer_mask){
                    timer_int_handler();

                    if(timerHandler() != 0){
                      destroyElements();
                      return EXIT_FAILURE;
                    }

                    swap_buffer();
                 }
                 break;
             default:
                 break; 
         }
     } else { 
     }
}

  if(kbd_unsubscribe_int() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(timer_unsubscribe_int() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(mouse_unsubscribe_int() != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  destroyElements();

  return EXIT_SUCCESS;

}

void (destroyElements)(){
  destroyPlayer1(player1);
  destroyPlayer2(player2);
  destroyBall(ball);
  freeXPMScore();
  free(background);
  free_second_buffer();
}

int (loadBackground)(){
  xpm_image_t img;
  background = (uint32_t *) xpm_load((xpm_map_t) Court_rec_xpm, XPM_8_8_8_8, &img);

  if(background == NULL)
    return EXIT_FAILURE;

  drawBackground(background);
  return EXIT_SUCCESS;
}

int (keyboardHandler)(){

  changePlayerMovementKBD(player1, get_scancode());

  return EXIT_SUCCESS;
}


int (timerHandler)(){

  if(refreshBackground(background) != 0){
    printf("Error while erasing the player1\n");
    return EXIT_FAILURE;
  };

  if (!canHitAfterServe) {
    if (ball->direction == UP_BALL) {
        if (ball->y <= NET_Y_POS) canHitAfterServe = true;
    } else {
        if (ball->y >= NET_Y_POS) canHitAfterServe = true;
    }
}

  if(player2->state != START){
    //disable the collision when the player 2 is starting because the ball starts out of the field
    if(checkCollisionLine(ball, background)){
        if(ball->y < 350){
          //player 1 scored
          resetBall(ball, PLAYER1);
          resetPlayer(player1, true);
          resetPlayer(player2, false);
          player1Score = player1Score + 1;

          if(updateXPMScore(1,player1Score) != 0){
            return EXIT_FAILURE;
          }

          canHitAfterServe = false;
        }
        else{
          //player 2 scored
          resetBall(ball, PLAYER2);
          resetPlayer(player1, false);
          resetPlayer(player2, true);
          player2Score = player2Score + 1;

          if(updateXPMScore(2,player2Score) != 0){
            return EXIT_FAILURE;
          }
          
          canHitAfterServe = false;
        }
        counter = 0;
      return EXIT_SUCCESS;
    }
  }

  if(player1 -> state == HIT){
    collisionPlayer(ball, player1);
  }

  if(player2-> state == HIT){
    collisionPlayer(ball, player2);
  }

  if((player1 ->state != CHOOSE_START) && (player1 ->state != CHOOSE_START_STOP) && (player2 ->state != CHOOSE_START) && (player2 ->state != CHOOSE_START_STOP)){
    if((player1->state == START) || (player2->state == START)){
      moveBall(ball,true);
    }
    else{
      moveBall(ball,false);
    }

    
    if(drawBall(ball) != 0){
      return EXIT_FAILURE;
    }
  }
  
  updatePlayerMovementsTimer(player1, counter, canHitAfterServe);

  updatePlayer2AI(player2,ball,counter,canHitAfterServe);
  
  if(drawPlayer(player2) != 0){
    return EXIT_FAILURE;
  }

  if(drawPlayer(player1) != 0){
    return EXIT_FAILURE;
  }

  if(drawScore(1) != 0){
    return EXIT_FAILURE;
  }

  if(drawScore(2) != 0){
    return EXIT_FAILURE;
  }

  if(drawScoreText() != 0){
    return EXIT_FAILURE;
  }

    return EXIT_SUCCESS;
}

int (mouseHandler)(){
  int newBallX = 9999; 
  updatePlayerMovementMouse(player1, get_mouse_packet().lb, &newBallX, canHitAfterServe);
  
  if(newBallX != 9999){
    //the player started and the ball position needs to be updated
    ball->x = newBallX;
  }
  return EXIT_SUCCESS;
}

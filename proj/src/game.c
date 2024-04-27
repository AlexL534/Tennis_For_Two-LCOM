#include "game.h"
#include "background.h"

static Player_state player_state = STOP;
static Player_movement player_movement = RIGHT_PLAYER;
//static Game_state game_state = GAME;
static Player1 *player1;

static uint32_t *background;

extern int counter;

int (gameLoop)(){
  
  if(loadBackground() != 0){
    return EXIT_FAILURE;
  }
  
  player1 = createPlayer1();
  drawPlayer1(player1);

  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  timer_set_frequency(0, 30);
  if(kbd_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }
  uint8_t kbc_mask = BIT(bit_no);

  if(timer_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }
  uint8_t timer_mask = BIT(bit_no);

  if(mouse_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }
  uint8_t mouse_mask = BIT(bit_no);

  while( get_scancode() != KBD_ESC_BREAK){
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
                 } 		
                 if (msg.m_notify.interrupts & kbc_mask) { 
                       kbc_ih();
                       keyboardHandler();
                 }
                 if(msg.m_notify.interrupts & timer_mask){
                    timer_int_handler();
                    timerHandler();
                 }
                 break;
             default:
                 break; 
         }
     } else { 
     }
}

  if(kbd_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  if(timer_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  if(mouse_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  destroyElements();

  return EXIT_SUCCESS;

}

void (destroyElements)(){
  destroyPlayer1(player1);
  free(background);
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

  if((player_state == MOVE) || (player_state == STOP)){
    
    if(get_scancode() == ARROW_LEFT){
      updateDirection(LEFTD, player1);
      player_state = MOVE;
      player_movement = LEFT_PLAYER;
    }

    else if(get_scancode() == ARROW_RIGHT){
      updateDirection(RIGHTD, player1);
      player_state = MOVE;
      player_movement = RIGHT_PLAYER;
    }

    else if(get_scancode() == ARROW_DOWN){
      player_state = MOVE;
      player_movement = DOWN_PLAYER;
    }

    else if(get_scancode() == ARROW_UP){
      player_state = MOVE;
      player_movement = UP_PLAYER;
    }

    else{
      player_state = STOP;
    }
  }

  return EXIT_SUCCESS;
}

int (timerHandler)(){
  switch (player_state)
  {
  case MOVE:
    //erase the player
    if(drawPortionOfBackground(background, player1->x, player1->y, player1->currentSprite.width,player1->currentSprite.height) != 0){
      printf("Error while erasing the player1\n");
      return EXIT_FAILURE;
    };

    //move the player and draws him in the new position
    movePlayer1(player1, player_movement);

    drawPlayer1(player1);

    if(counter % 5 == 0){
      moveAnim1(player1);
    }
    break;
  case HIT:
    //erase the player
    if(drawPortionOfBackground(background, player1->x, player1->y, player1->currentSprite.width,player1->currentSprite.height) != 0){
      printf("Error while erasing the player1\n");
      return EXIT_FAILURE;
    };

    drawPlayer1(player1);

    if(counter % 5 == 0){
      hitAnim1(player1);

      //the animation ended
      if(player1->hitanim == 0){
        player_state = STOP;
      }
    }
    break;

  default:

    break;
  }

    return EXIT_SUCCESS;
}

int (mouseHandler)(){
  if(get_mouse_packet().lb){
    player_state = HIT;
  }

  return EXIT_SUCCESS;
}

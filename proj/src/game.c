#include "game.h"
#include "background.h"

static Player_state player1_state = CHOOSE_START_STOP;
static Player_movement player1_movement = RIGHT_PLAYER;
//static Game_state game_state = GAME;
static Player *player1;
static Player *player2;

static uint32_t *background;

extern int counter;

int (gameLoop)(){
  
  if(loadBackground() != 0){
    return EXIT_FAILURE;
  }
  
  player1 = createPlayer1();
  player2 = createPlayer2();
  drawPlayer(player1);
  draw_xpm((xpm_map_t) very_large_ball_xpm,XPM_8_8_8_8, 100,100 );

  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  timer_set_frequency(0, 60);
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
  destroyPlayer2(player2);
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

  if((player1_state == MOVE) || (player1_state == STOP)){
    
    if((get_scancode() == ARROW_LEFT) || (get_scancode() == A_KEY)){
      updateDirection(LEFTD, player1);
      player1_state = MOVE;
      player1_movement = LEFT_PLAYER;
    }

    else if((get_scancode() == ARROW_RIGHT) || (get_scancode() == D_KEY)){
      updateDirection(RIGHTD, player1);
      player1_state = MOVE;
      player1_movement = RIGHT_PLAYER;
    }

    else if((get_scancode() == ARROW_DOWN) || (get_scancode() == S_KEY)){
      player1_state = MOVE;
      player1_movement = DOWN_PLAYER;
    }

    else if((get_scancode() == ARROW_UP) || (get_scancode() == W_KEY)){
      player1_state = MOVE;
      player1_movement = UP_PLAYER;
    }

    else if(stopPlayer(get_scancode(), player1_movement)){
      player1_state = STOP;
    }

  }
  else if((player1_state == CHOOSE_START) || (player1_state == CHOOSE_START_STOP)){
    if((get_scancode() == ARROW_LEFT) || (get_scancode() == A_KEY)){
      updateDirection(LEFTD, player1);
      player1_movement = LEFT_PLAYER;
      player1_state = CHOOSE_START;
    }

    else if((get_scancode() == ARROW_RIGHT) || (get_scancode() == D_KEY)){
      updateDirection(RIGHTD, player1);
      player1_movement = RIGHT_PLAYER;
      player1_state = CHOOSE_START;
    }
    else{
      player1_state = CHOOSE_START_STOP;
    }
  }

  return EXIT_SUCCESS;
}

bool (stopPlayer)(uint8_t scancode, Player_movement movement){
  switch (movement)
  {
  case UP_PLAYER:
    if((scancode == (KBD_BREAKCODE | ARROW_UP)) || (scancode == (KBD_BREAKCODE | W_KEY))){
      return true;
    }
    break;
  
  case DOWN_PLAYER:
    if((scancode == (KBD_BREAKCODE | ARROW_DOWN)) || (scancode == (KBD_BREAKCODE | S_KEY))){
      return true;
    }
    break;

  case RIGHT_PLAYER:
    if((scancode == (KBD_BREAKCODE | ARROW_RIGHT)) || (scancode == (KBD_BREAKCODE | D_KEY))){
      return true;
    }
    break;

  case LEFT_PLAYER:
    if((scancode & (KBD_BREAKCODE | ARROW_LEFT)) || (scancode & (KBD_BREAKCODE | A_KEY))){
      return true;
    }
    break;

  default:

    break;
  }

  return false;
}

int (timerHandler)(){
    if(refreshBackground(background) != 0){
      printf("Error while erasing the player1\n");
      return EXIT_FAILURE;
    };
  drawPlayer(player2);

  switch (player1_state)
  {

  case MOVE:

    //move the player and draws him in the new position
    movePlayer(player1, player1_movement);

    

    if(counter % 6 == 0){
      moveAnim(player1);
    }
    break;

  case HIT:

    if(counter % 3 == 0){
      hitAnim(player1);

      //the animation ended
      if(player1->hitanim == 0){
        player1_state = STOP;
      }
    }
    break;

  case CHOOSE_START:


    chooseStartAnim(player1);
    movePlayer(player1, player1_movement);

    break;

  case START:


    if(counter % 3 == 0){
      startAnim(player1);

      //the animation ended
      if(player1->startanim == 0){
        player1_state = STOP;
      }
    }
    break;
  default:

    break;
  }

  drawPlayer(player1);

    return EXIT_SUCCESS;
}

int (mouseHandler)(){
  if((player1_state == CHOOSE_START) || (player1_state == CHOOSE_START_STOP)){
    if(get_mouse_packet().lb){
      player1_state = START;
  }
  }
  else{
    if(get_mouse_packet().lb){
      player1_state = HIT;
    }
  }
  return EXIT_SUCCESS;
}

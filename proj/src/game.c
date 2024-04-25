#include "game.h"

static Player_state player_state = STOP;
//static Game_state game_state = GAME;
static Player1 *player1;

extern int counter;

int (gameLoop)(){

  player1 = createPlayer1();

  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(kbd_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }
  uint8_t kbc_mask = BIT(bit_no);

  if(timer_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }
  uint8_t timer_mask = BIT(bit_no);

  while( get_scancode() != KBD_ESC_BREAK){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { 
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: 		
                 if (msg.m_notify.interrupts & kbc_mask) { 
                       kbc_ih();
                       keyboardhandler();
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

  return EXIT_SUCCESS;

}

void (keyboardhandler)(){
  if(get_scancode() == ARROW_LEFT){
    updateDirection(LEFT, player1);
    player_state = MOVE;
  }

  else if(get_scancode() == ARROW_RIGHT){
    updateDirection(RIGHT, player1);
    player_state = MOVE;
  }

  else{
    player_state = STOP;
  }
}

void (timerHandler)(){
    if(player_state == MOVE){
      movePlayer1(player1);
      if(counter % 5 == 0){
        moveAnim1(player1);
      }
    }

}

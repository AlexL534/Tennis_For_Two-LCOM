#include "game.h"
#include "background.h"

static Game_state game_state = START_MENU;
static Menu* menu;
static Mouse *mouse;
static Player *player1;
static Player *player2;
static Ball *ball;
int player1Score = 0;
int player2Score = 0;
static bool canHitAfterServe = false;
bool isStartMenu=true;
bool initial_load=false;

static uint32_t *background;

extern int counter;

int (gameLoop)(){
  
  player1 = createPlayer1();
  player2 = createPlayer2();
  ball = createBall();
  mouse = createMouse();

  menu = initialize_menu(isStartMenu);

  if(menu == NULL){
    printf("menu is null");
    return EXIT_FAILURE;
  }

  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  uint8_t day;
  uint8_t month;
  uint8_t year;

  //command to change the mouse sample rate
  if(mouse_write_byte(0XF3) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  //changes the mouse sample rate to 20
  if(mouse_write_byte(0X14) != 0){
    destroyElements();
    return EXIT_FAILURE;
  }

  //enables the data report for the mouse
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

  while(game_state != QUIT){
    if((game_state == GAME) && ((player1Score >= 10) || (player2Score >= 10))){
      if(clear_screen()!=0){
        return EXIT_FAILURE;
      }
      game_state = START_MENU;
      player1Score=0;
      player2Score=0;
      menu=initialize_menu(true);
    }

    if (game_state == RESTART) {
      if(clear_screen()!=0){
        return EXIT_FAILURE;
      }
      player1Score=0;
      player2Score=0;
      game_state = GAME;

      if(updateXPMScore(1,player2Score) != 0){
        return EXIT_FAILURE;
      }

      if(updateXPMScore(2,player2Score) != 0){
        return EXIT_FAILURE;
      }

    }

    if (game_state == GAME && (get_scancode() == KBD_ESC_BREAK)) {
      set_scancode(0x01);
      game_state = PAUSE_MENU;
      menu = initialize_menu(false);
    }

    if(initial_load && (game_state == GAME)){

      if(loadBackground() != 0){
        destroyElements();
        printf("background failed");
        return EXIT_FAILURE;
      }

      if(loadInitialXPMScore() != 0){
        printf("score failed");
        destroyElements();
        return EXIT_FAILURE;
      }
    }
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) { 
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if(msg.m_notify.interrupts & timer_mask){
            timer_int_handler();
            switch (game_state) {

              case START_MENU:
                if(time_handler_menu(menu, mouse) !=0){
                  printf("menu timer handler failed");
                  destroyElements();
                  return EXIT_FAILURE;
                }
                get_date(&day,&month,&year);
                draw_date(day,month,year);
                break;

              case GAME: 
                if(timerHandler() != 0){
                  destroyElements();
                  return EXIT_FAILURE;
                }
                break;
              
              case PAUSE_MENU:
                if (drawPause(menu) != 0 || drawMouse(mouse) != 0) {
                  destroyElements();
                  return EXIT_FAILURE;
                }
                break;

              default:
                printf("default");
                break;
            }

            swap_buffer();
          }
          if (msg.m_notify.interrupts & kbc_mask) { 
            kbc_ih();
            switch (game_state) {

              case START_MENU:
                kbd_handler_menu(&game_state,menu);
                if(game_state==GAME){
                  initial_load=true;
                }
                break;

              case GAME:
                initial_load=false;
                keyboardHandler();
                break;

              case PAUSE_MENU:
                update_selected_pause(get_scancode(), &game_state, menu);
                break;

              default:
                break;
            }       
          }
          if (msg.m_notify.interrupts & mouse_mask) {
            mouse_ih();
            mouse_insert_byte();
            if (get__mouse_byte_index() == 3) {
              mouse_insert_in_packet();
              if (game_state == PAUSE_MENU) {
                update_selected_mouse(menu, mouse, &game_state);
                if (game_state != PAUSE_MENU) {
                  clear_mouse_packet();
                  // Clear screen and reinitialize menu if game_state changes
                  if (clear_screen() != 0) {
                      destroyElements();
                      return EXIT_FAILURE;
                  }
                  if (game_state == GAME) {
                      initial_load = true; // Ensure background and scores are loaded
                  }
                }
              }
              if (mouseHandler() != 0) {
                destroyElements();
                return EXIT_FAILURE;
              }
              reset_byte_index();
            }
          }
          break;
      } 	
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
  destroyMouse(mouse);
  freeXPMScore();
  free(background);
  free_second_buffer();
  free(menu->play_button.map);
  free(menu->quit.map);
  free(menu->play_button_hover.map);
  free(menu->quit_hover.map);
  free(menu->title.map);
  free(menu->pause_menu.map);
  free(menu->resume.map);
  free(menu->resume_hover.map);
  free(menu->restart.map);
  free(menu->restart_hover.map);
  free(menu->quit_pause.map);
  free(menu->quit_pause_hover.map);
  free(menu);
  menu=NULL;
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
  static bool scored = false; // Static flag to persist across function calls

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
      scored = true;
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
  scored = false; 
  return EXIT_SUCCESS;
}

int (mouseHandler)(){
  int newBallX = 9999; 
  updatePlayerMovementMouse(player1, get_mouse_packet().lb, &newBallX, canHitAfterServe);
  updateMousePosition(mouse, get_mouse_packet().delta_x, get_mouse_packet().delta_y);
  if(newBallX != 9999){
    //the player started and the ball position needs to be updated
    ball->x = newBallX;
  }
  return EXIT_SUCCESS;
}

#include "player.h"
#include "devices/video.h"
#include "color.h"

Player *(createPlayer1)(){
  Player *player = (Player*)malloc(sizeof(Player));

  if( player == NULL){
    return NULL;
  }

  player->x = 400;
  player->y = 690;
  player->xspeed = 6;
  player->yspeed = 6;
  player->moveanim = 0;
  player->startanim = 0;
  player->hitanim = 0;
  player->player_numb = PLAYER1;

  xpm_image_t img;
  Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));

  sprite->map = (uint32_t *)malloc(sizeof(char*));

  //load the move sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move1_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->move[0] = *sprite;


  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->move[1] = *sprite;

  //load the move_rev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move1_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->moverev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->moverev[1] = *sprite;

  //load the hit sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit1_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit3_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[2] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit4_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[3] = *sprite;

  //load the hitrev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit1_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit3_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[2] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit4_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[3] = *sprite;

  //load the starting sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start1_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[0] = *sprite;

  player->currentSprite = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start3_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[2] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start4_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[3] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start5_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[4] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start6_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[5] = *sprite;

  //load the start rev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start1_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start3_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[2] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start4_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[3] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start5_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[4] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start6_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[5] = *sprite;

  player->direction = RIGHTD;

  free(sprite->map);
  free(sprite);

  return player;
}

Player *(createPlayer2)(){
  Player *player = (Player*)malloc(sizeof(Player));

  if( player == NULL){
    return NULL;
  }

  player->x = 400;
  player->y = 200;
  player->xspeed = 6;
  player->yspeed = 6;
  player->moveanim = 0;
  player->startanim = 0;
  player->hitanim = 0;
  player->player_numb = PLAYER2;

  xpm_image_t img;
  Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));

  sprite->map = (uint32_t *)malloc(sizeof(char*));

  //load the move sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move1_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->move[0] = *sprite;


  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move2_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->move[1] = *sprite;

  //load the move_rev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move1_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->moverev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move2_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->moverev[1] = *sprite;

  //load the hit sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit1_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit2_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hit[1] = *sprite;


  //load the hitrev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit1_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) hit2_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->hitrev[1] = *sprite;


  //load the starting sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start1_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[0] = *sprite;

  player->currentSprite = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start2_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start3_2_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->start[2] = *sprite;


  //load the start rev sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start1_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[0] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start2_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[1] = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) start3_2_rev_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->startrev[2] = *sprite;

  player->direction = RIGHTD;

  return player;
}

int (drawPlayer)(Player *player){
  int width = player->currentSprite.width;
  int height = player->currentSprite.height;
  uint32_t *map = player->currentSprite.map;

  for(int j =  player->y ; j < player->y + height; j++){
    for(int i = player->x ; i < player->x + width; i++){
      if(*map != TRANSPARENCY_COLOR){
        if(vg_draw_color(i,j,*map) != 0){
          return EXIT_FAILURE;
        }
      }
      map++;
    }
  }
  return EXIT_SUCCESS;
}

void (updateDirection)(Player_direction direction, Player *player){
  player->direction = direction;
}

void (get_current_hit_limits)(Player *player, int *x_min, int *x_max, int *y_min, int *y_max){
  switch (player->player_numb)
  {
  case PLAYER1:
      if(player->direction == RIGHT_PLAYER){
        *x_min = HIT_P1_X_MIN;
        *x_max = HIT_P1_X_MAX;
        *y_min = HIT_P1_Y_MIN;
        *y_max = HIT_P1_Y_MAX;
      }
      else{
        *x_min = HIT_REV_P1_X_MIN;
        *x_max = HIT_REV_P1_X_MAX;
        *y_min = HIT_P1_Y_MIN;
        *y_max = HIT_P1_Y_MAX;
      }
    break;
  
  case PLAYER2:
    if(player->direction == RIGHT_PLAYER){
        *x_min = HIT_REV_P2_X_MIN;
        *x_max = HIT_REV_P2_X_MAX;
        *y_min = HIT_P2_Y_MIN;
        *y_max = HIT_P2_Y_MAX;
      }
      else{
        *x_min = HIT_P2_X_MIN;
        *x_max = HIT_P2_X_MAX;
        *y_min = HIT_P2_Y_MIN;
        *y_max = HIT_P2_Y_MAX;
      }
    break;
  }
}

void (movePlayer)(Player *player, Player_movement movement){
  int new_x = player->x;
  int new_y = player->y;

  switch (movement)
  {
    //changes the player position accordingly to their movement
  case RIGHT_PLAYER:
    new_x += player->xspeed;
    break;
  case LEFT_PLAYER:
    new_x -= player->xspeed;
    break;
  case UP_PLAYER:
    new_y -= player->yspeed;
    break;
  case DOWN_PLAYER:
    new_y += player->yspeed;
    break;
  
  default:
    break;
  }

  //corrects the player position to avoid it from going out of the screen
  if (new_x < MIN_X) {
        new_x = MIN_X;
    } else if (new_x + player->currentSprite.width > MAX_X) {
        new_x = MAX_X - player->currentSprite.width;
    }

  if (new_y < MIN_Y) {
        new_y = MIN_Y;
    } else if (new_y + player->currentSprite.height > MAX_Y) {
        new_y = MAX_Y - player->currentSprite.height;
    }

    player->x = new_x;
    player->y = new_y;

}

void (moveAnim)(Player *player){
  unsigned int moveanim = player->moveanim;
  if(player->direction == RIGHTD){
    player->currentSprite = player->move[moveanim];
  } else{
    player->currentSprite = player->moverev[moveanim];
  }

  moveanim++;

  if(moveanim == 2){
    moveanim = 0;
  }

  player->moveanim = moveanim;
}

void(hitAnim)(Player *player){
  unsigned int hitanim = player->hitanim;
  if(player->direction == RIGHTD){
    player->currentSprite = player->hit[hitanim];
  } else{
    player->currentSprite = player->hitrev[hitanim];
  }

  hitanim++;

  if(player->player_numb == PLAYER1){
    if(hitanim == 4){
      hitanim = 0;
    }
  }
  else if(player->player_numb == PLAYER2){
    if(hitanim == 2){
      hitanim = 0;
    }
  }

  player->hitanim = hitanim;
}

void (startAnim)(Player *player){
  unsigned int startanim = player->startanim;
  if(player->direction == RIGHTD){
    player->currentSprite = player->start[startanim];
  } else{
    player->currentSprite = player->startrev[startanim];
  }

  startanim++;

  if(player->player_numb == PLAYER1){
    if(startanim == 6){
      startanim = 0;
    }
  }
  else if(player->player_numb == PLAYER2){
    if(startanim == 3){
      startanim = 0;
    }
  }

  player->startanim = startanim;
}

void (chooseStartAnim)(Player *player){
  if(player->direction == RIGHTD){
    player->currentSprite = player->start[0];
  }
  else{
    player->currentSprite = player->startrev[0];
  }
}

void (destroyPlayer1)(Player *player){
  //if the player isn't the player 1, changes function
  if(player->player_numb == PLAYER2){
    destroyPlayer2(player);
    return;
  }

  if(player == NULL){
    return;
  }

  //free the memory allocated for the currrent sprite
  if(player -> currentSprite.map){
    free(player -> currentSprite.map);
  }

  //free the allocated memory for the move arrays
  for(int i = 0; i < 2 ; i++){
    if(player -> move[i].map){
      free(player -> move[i].map);
    }
    if(player -> moverev[i].map){
      free(player -> moverev[i].map);
    }
  }

  //free the allocated memory for the hit arrays
  for(int i = 0; i < 4; i++){
    if(player -> hit[i].map){
      free(player ->hit[i].map);
    }
    if(player->hitrev[i].map){
      free(player->hitrev[i].map);
    }
  }

  //free the allocated memory for the start arrays
  for(int i = 0; i < 6; i++){
    if(player -> start[i].map){
      free(player ->start[i].map);
    }
    if(player ->startrev[i].map){
      free(player -> startrev[i].map);
    }
  }

  free(player);
  player = NULL;
}

void (destroyPlayer2)(Player * player){
  //if the player isn't the player 2, changes function
  if(player->player_numb == PLAYER1){
    destroyPlayer1(player);
    return;
  }

  if(player == NULL){
    return;
  }

  //free the memory allocated for the currrent sprite
  if(player -> currentSprite.map){
    free(player -> currentSprite.map);
  }

  //free the allocated memory for the move arrays
  for(int i = 0; i < 2 ; i++){
    if(player -> move[i].map){
      free(player -> move[i].map);
    }
    if(player -> moverev[i].map){
      free(player -> moverev[i].map);
    }
  }

  //free the allocated memory for the hit arrays
  for(int i = 0; i < 2; i++){
    if(player -> hit[i].map){
      free(player ->hit[i].map);
    }
    if(player->hitrev[i].map){
      free(player->hitrev[i].map);
    }
  }

  //free the allocated memory for the start arrays
  for(int i = 0; i < 3; i++){
    if(player -> start[i].map){
      free(player ->start[i].map);
    }
    if(player ->startrev[i].map){
      free(player -> startrev[i].map);
    }
  }

  free(player);
  player = NULL;
}

#include "player1.h"
#include "devices/video.h"
#include "color.h"

static unsigned int moveanim = 0;

Player1 *(createPlayer1)(){
  Player1 *player = (Player1*)malloc(sizeof(Player1));

  if( player == NULL){
    return NULL;
  }

  player->x = 400;
  player->y = 550;
  player->xspeed = 5;
  player->yspeed = 5;

  xpm_image_t img;
  Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));

  sprite->map = (uint32_t *)malloc(sizeof(char*));

  //load the move sprites
  sprite->map = (uint32_t *) xpm_load((xpm_map_t) move1_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  player->move[0] = *sprite;

  player->currentSprite = *sprite;

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

  player->isHitting = false;
  player->isStarting = false;

  player->direction = RIGHTD;

  return player;
}

int (drawPlayer1)(Player1 *player){
  int width = player->currentSprite.width;
  int height = player->currentSprite.height;
  uint32_t *map = player->currentSprite.map;

  for(int j =  player->y ; j < player->y + height; j++){
    for(int i = player->x ; i < player->x + width; i++){
      if(*map != TRANSPARENCY_COLOR)
        vg_draw_color(i,j,*map);
      map++;
    }
  }
  return EXIT_SUCCESS;
}

void (updateDirection)(Player_direction direction, Player1 *player){
  player->direction = direction;
}

void (movePlayer1)(Player1 *player, Player_movement movement){
  if(movement == RIGHT_PLAYER){
    player->x += player->xspeed;
  };
  if(movement == LEFT_PLAYER){
    player->x -= player->xspeed;
  }
  if(movement == UP_PLAYER){
    player->y -= player->yspeed;
  }
  if(movement == DOWN_PLAYER){
    player->y += player->yspeed;
  }

  drawPlayer1(player);
}

void (moveAnim1)(Player1 *player){
  if(player->direction == RIGHTD){
    player->currentSprite = player->move[moveanim];
  } else{
    player->currentSprite = player->moverev[moveanim];
  }

  moveanim++;

  if(moveanim == 2){
    moveanim = 0;
  }
}

void (destroyPlayer1)(Player1 *player){
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

  free(player);
  player = NULL;
}

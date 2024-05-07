#include "ball.h"
#include "devices/video.h"
#include "color.h"

Ball *(createBall)(){
  Ball *ball = (Ball*)malloc(sizeof(Ball));

  if(ball == NULL){
    return NULL;
  }

  ball->x = 410;
  ball->y = 690;
  ball->xspeed = 8;
  ball->yspeed = 8;
  ball->incline = 0;
  ball->direction = UP_BALL_START;

  xpm_image_t img;
  Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));

  sprite->map = (uint32_t *)malloc(sizeof(char*));

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) medium_ball_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  ball->medium = *sprite;
  ball->currentSprite = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) small_ball_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  ball->small = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) large_ball_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  ball->large = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) very_large_ball_xpm, XPM_8_8_8_8, &img);
  sprite->width = img.width;
  sprite->height = img.height;
  ball->very_large = *sprite;

  return ball;
}

int (drawBall)(Ball *ball){
  int width = ball->currentSprite.width;
  int height = ball->currentSprite.height;
  uint32_t *map = ball->currentSprite.map;

  for(int j = ball->y; j < ball->y + height; j++){
    for(int i = ball->x; i < ball->x + width; i++){
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

void (updateDirection)(Ball_direction direction, Ball *ball){
  ball->direction = direction;
}

void (destroyBall)(Ball *ball){
  if(ball == NULL){
    return;
  }

  if(ball->currentSprite.map != NULL){
    free(ball ->currentSprite.map);
  }

  if(ball->small.map != NULL){
    free(ball->small.map);
  }

  if(ball ->medium.map != NULL){
    free(ball->medium.map);
  }

  if(ball ->large.map != NULL){
    free(ball->large.map);
  }

  if(ball ->very_large.map != NULL){
    free(ball->very_large.map);
  }

  free(ball);
  ball = NULL;
}
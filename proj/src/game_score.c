#include "game_score.h"

static Sprite p1;
static Sprite p2;
static Sprite p1Score;
static Sprite p2Score;

int (loadInitialXPMScore)(){
  xpm_image_t img;
  Sprite *sprite = (Sprite*)malloc(sizeof(Sprite));

  sprite->map = (uint32_t *)malloc(sizeof(char*));

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) p1_xpm, XPM_8_8_8_8, &img);
  sprite->height = img.height;
  sprite->width = img.width;
  p1 = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) p2_xpm, XPM_8_8_8_8, &img);
  sprite->height = img.height;
  sprite->width = img.width;
  p2 = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) r0_xpm, XPM_8_8_8_8, &img);
  sprite->height = img.height;
  sprite->width = img.width;
  p1Score = *sprite;

  sprite->map = (uint32_t *) xpm_load((xpm_map_t) r0_xpm, XPM_8_8_8_8, &img);
  sprite->height = img.height;
  sprite->width = img.width;
  p2Score = *sprite;

  if((p1.map == NULL) || (p2.map == NULL) || (p1Score.map == NULL) || (p2Score.map == NULL)){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int (drawScore)(int playerNumb){
  switch(playerNumb){
    case 1:
      int width = p1Score.width;
      int height = p1Score.height;
      uint32_t *map = p1Score.map;

      for(int j =  130 ; j < 130 + height; j++){
        for(int i = 1035 ; i < 1035 + width; i++){
          if(*map != TRANSPARENCY_SCORE){
            if(vg_draw_color(i,j,*map) != 0){
              return EXIT_FAILURE;
            }
          }
          map++;
        }
      }
      return EXIT_SUCCESS;
    
    case  2:
      int width = p2Score.width;
      int height = p2Score.height;
      uint32_t *map = p2Score.map;

      for(int j =  230 ; j < 230 + height; j++){
        for(int i = 1035 ; i < 1035 + width; i++){
          if(*map != TRANSPARENCY_SCORE){
            if(vg_draw_color(i,j,*map) != 0){
              return EXIT_FAILURE;
            }
          }
          map++;
        }
      }
      return EXIT_SUCCESS;
  }
}

int (updateXPMScore)(int playerNumb, int score){
  xpm_image_t img;

  switch (playerNumb)
  {
  case 1:
    chooseXPMScore(score, p1Score.map, &img);

    if(p1Score.map == NULL){
      return EXIT_FAILURE;
    }

    p1Score.height = img.height;
    p1Score.width = img.width;
    break;

  case 2:
    chooseXPMScore(score, p2Score.map, &img);

    if(p2Score.map == NULL){
      return EXIT_FAILURE;
    }

    p2Score.height = img.height;
    p2Score.width = img.width;
    break;
  default:
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;

}

void (chooseXPMScore)(int score, uint32_t *xpm, xpm_image_t *img){

  switch(score){
    case 0:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r0_xpm, XPM_8_8_8_8, img);
      break;
    case 1:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r1_xpm, XPM_8_8_8_8, img);
      break;
    case 2:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r2_xpm, XPM_8_8_8_8, img);
      break;
    case 3:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r3_xpm, XPM_8_8_8_8, img);
      break;
    case 4:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r4_xpm, XPM_8_8_8_8, img);
      break;
    case 5:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r5_xpm, XPM_8_8_8_8, img);
      break;
    case 6:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r6_xpm, XPM_8_8_8_8, img);
      break;
    case 7:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r7_xpm, XPM_8_8_8_8, img);
      break;
    case 8:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r8_xpm, XPM_8_8_8_8, img);
      break;
    case 9:
      xpm = (uint32_t *) xpm_load((xpm_map_t) r9_xpm, XPM_8_8_8_8, img);
      break;
    default:
      //cannot have a score bigger than 9
      break;
  }
}
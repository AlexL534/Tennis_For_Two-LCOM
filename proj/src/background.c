#include "background.h"
#include "devices/video.h"
#include "xpms.h"


int (drawBackground)(uint32_t *background){

  xpm_image_t img;
  background = (uint32_t *) xpm_load((xpm_map_t) Court_rec_xpm, XPM_8_8_8_8, &img);
  uint32_t *ptr = background;
  for(int i = 0; i < img.height; i++){
    for(int j = 0; j < img.width; j++){
      if(vg_draw_color(j, i, *ptr) != 0){
        return EXIT_FAILURE;
      };
      ptr++;
    }
  }
  return EXIT_SUCCESS;
}

int (initializeMenuBackground)(uint32_t *background, bool isStart, Menu *menu){

  uint32_t color = 0x000000;

  uint32_t *ptr = background;
  for(int i = 0; i < (int) get_vres(); i++){
    for(int j = 0; j < (int) get_hres(); j++){
      if(memcpy(ptr, &color, get_bytes_per_pixel()) == NULL){
        return EXIT_FAILURE;
      };
      ptr++;
    }
  }

  if(isStart){
    uint32_t *title_map = menu->title.map;

    if(title_map == NULL){
      printf("No title sprite found");
      return EXIT_FAILURE;
    }

    int width = menu->title.width;
    int height = menu->title.height;
    int x_offset = 260;
    int y_offset = 10;
    
    uint32_t *ptr2 = title_map;
    for(int i = y_offset; i < y_offset + height; i++){
      for(int j = x_offset; j < x_offset + width; j++){

          unsigned int index = (j + i * get_hres());
          

          if(index >= (get_vres() * get_hres())){
            printf("here");
          }
        if(*ptr2 != TRANSPARENCY_COLOR && i < MAX_X && j < MAX_Y){

          if(memcpy(&background[index], ptr2 , get_bytes_per_pixel()) == NULL){ 
            return EXIT_FAILURE;
          };
        }
        ptr2++;
      }

    }
  }
  else{
    uint32_t *title_map = menu->pause_menu.map;

    if(title_map == NULL){
      printf("No title sprite found");
      return EXIT_FAILURE;
    }

    int width = menu->pause_menu.width;
    int height = menu->pause_menu.height;

    
    uint32_t *ptr2 = title_map;
    for(int i = 0; i < 0 + height; i++){
      for(int j = 0; j < 0 + width; j++){

          unsigned int index = (j + i * get_hres());
          

          if(index >= (get_vres() * get_hres())){
            printf("here");
          }
        if(*ptr2 != TRANSPARENCY_COLOR && i < MAX_X && j < MAX_Y){

          if(memcpy(&background[index], ptr2 , get_bytes_per_pixel()) == NULL){ 
            return EXIT_FAILURE;
          };
        }
        ptr2++;
      }

    }
  }

  return EXIT_SUCCESS;
}

int (refreshBackground)(uint32_t *background){

  if(memcpy(get_second_buffer(), background, get_hres() * get_vres() * get_bytes_per_pixel()) == NULL){
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}



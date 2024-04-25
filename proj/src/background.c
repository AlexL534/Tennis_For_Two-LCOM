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

int (drawPortionOfBackground)(uint32_t *background, uint16_t x, uint16_t y, uint16_t widht, uint16_t height){
  
  uint32_t *ptr = background;
  for(int i = y; i <= y + height; i++){
    for(int j = x; j <= x + widht; j++){
      if (i < (int)get_vres() - 1 && j < (int)get_hres() - 1)
        if(vg_draw_color(j, i, *(ptr + (get_hres() * i + j))) != 0){
          return EXIT_FAILURE;
        };

    }
  }
  return EXIT_SUCCESS;
}

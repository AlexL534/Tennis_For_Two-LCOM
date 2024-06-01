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

int (initializeMenuBackground)(uint32_t *background){

  background = (uint32_t *)malloc(get_hres() * get_vres() * get_bytes_per_pixel());
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

  return EXIT_SUCCESS;
}

int (refreshBackground)(uint32_t *background){
  
  if(memcpy(get_second_buffer(), background, get_hres() * get_vres() * get_bytes_per_pixel()) == NULL){
    return EXIT_FAILURE;
  };
  return EXIT_SUCCESS;
}



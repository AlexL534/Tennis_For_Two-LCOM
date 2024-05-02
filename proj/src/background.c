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

int (refreshBackground)(uint32_t *background){
  
  memcpy(get_second_buffer(), background, get_hres() * get_vres() * get_bytes_per_pixel());
  return EXIT_SUCCESS;
}

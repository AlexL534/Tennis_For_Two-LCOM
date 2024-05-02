#include <lcom/lcf.h>
#include "video.h"
#include "VBE.h"
#include <lcom/xpm.h>

static vbe_mode_info_t mode_info;
static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

//getters =====================================================
char *(get_video_mem)(){
  return video_mem;
}
vbe_mode_info_t (get_mode_inf)(){
  return mode_info;
}

unsigned (get_hres)(){
  return h_res;
}

unsigned (get_vres)(){
  return v_res;
}

unsigned (get_bits_per_pixel)(){
  return bits_per_pixel;
}

unsigned (get_bytes_per_pixel)(){
  return (bits_per_pixel + 7) / 8;
}

// =================================================================


//initializes the VRAM memory space
int (map_VRAM)(uint16_t mode){

  //initialize the variable with zeros (an error may occur if this step is jumped)
  memset(&mode_info, 0, sizeof(mode_info));

  //gets the VBE information about the mode we selected
  if(vbe_get_mode_info(mode, &mode_info) != 0){
    return EXIT_FAILURE;
  }

  //initializes the global variables
  bits_per_pixel = mode_info.BitsPerPixel;
  h_res = mode_info.XResolution;
  v_res = mode_info.YResolution;

  //calculates the buffer size (we add 7 because we need to round by excess)
  unsigned int size = (h_res * v_res * get_bytes_per_pixel());

  //calculate the memory base and limit
  struct minix_mem_range mr;
  mr.mr_base = (phys_bytes) mode_info.PhysBasePtr;	
  mr.mr_limit = mr.mr_base + size;  

  //grants the process premission to map the memory
  int r;
  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return EXIT_FAILURE;
  }

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, size);

  if(video_mem == MAP_FAILED){
    panic("couldn't map video memory");
    return EXIT_FAILURE;
  }

  //initializes the Minix Graphics mode =============================
  reg86_t reg;

  memset(&reg, 0, sizeof(reg));

  reg.ax = VBE_SET_VIDEO_MODE;
   // VBE call, function 02 -- set VBE mode
  reg.bx = VBE_SET_LINER_MODE | mode;
   // set bit 14: linear framebuffer
  reg.intno = VBE_SERVICE;

  if( sys_int86(&reg) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;

}


//draws a pixel in the screen
int (vg_draw_color)(uint16_t x, uint16_t y, uint32_t color){
  //verify if the coordinates are legal
  if((x > h_res) || (y > v_res) || ( x < 0) || (y < 0)){
    printf("Invalid Coordinates\n");
    return EXIT_FAILURE;
  }

  //calculates the vram index
  // hres * y is the number of bits needed to reach line y. Then we add x to get the index in that line
  unsigned int vram_index = (h_res * y  + x) * get_bytes_per_pixel();

  char * base_ptr = video_mem + vram_index;

  if(memcpy(base_ptr, &color, get_bytes_per_pixel()) == NULL){
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}


//draws a line with a specific color
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){

  for(int i = 0; i < len; i++){
    //draws a pixel in a given coordinate
    if(vg_draw_color(x + i, y, color) != 0){
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}


//draws a rectangle with a specific color
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){

  for(int i = 0; i < height; i++){
    //draws a line starting in the given coordinates and with a specific width
    if(vg_draw_hline(x, y + i, width, color) != 0){
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}

//draws a xpm image on the screen
int (draw_xpm)(xpm_map_t xpm, enum xpm_image_type type, uint16_t x, uint16_t y){
  xpm_image_t img; // pixmap and metadata
  uint32_t *map; // pixmap itself
  // get the pixmap from the XPM
  map = (uint32_t *) xpm_load(xpm, type, &img);
  //loops throught the pixmap and draws the color on the screen
  for(int i = 0; i < img.height; i++){
    for(int j = 0; j < img.width; j++){
      if(vg_draw_color(x + j, y + i, *map) != 0){
        return EXIT_FAILURE;
      };
      map++;
    }
  }
  return EXIT_SUCCESS;
}

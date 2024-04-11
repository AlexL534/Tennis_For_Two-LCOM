// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "VBE.h"
#include "kbd.c"
#include "utils.c"
#include "i8042.h"
#include "timer.c"

extern uint8_t scancode;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(KBD_wait_ESC)() {
  
  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(kbc_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }

  uint8_t irq_set = BIT(bit_no);

  while(scancode != KBD_ESC_BREAK){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                       kbc_ih();
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */	
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
}

  if(kbc_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  
  //initializes the graphics mode
  if(intialize_graphics_mode(mode) != 0){
    return EXIT_FAILURE;
  }

  //delays for a few seconds
  sleep(delay);

  //resets the graphics mode to text mode
  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  
  
  //Map the vram
  if(map_VRAM(mode) != 0){
    return EXIT_FAILURE;
  }

  //Initializes the graphics mode
  if(intialize_graphics_mode(mode) != 0){
    return EXIT_FAILURE;
  }

  //draws the rectangle
  if(vg_draw_rectangle(x,y,width,height,color) != 0){
    return EXIT_FAILURE;
  }

  //wait esc
  if(KBD_wait_ESC() != 0){
    return EXIT_FAILURE;
  }

  //exits the graphics mode
  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  //Map the vram
  if(map_VRAM(mode) != 0){
    return EXIT_FAILURE;
  }

  //Initializes the graphics mode
  if(intialize_graphics_mode(mode) != 0){
    return EXIT_FAILURE;
  }

  //finds the width and height of each rectangle
  uint16_t rectangle_width = get_hres() / no_rectangles;
  uint16_t rectangle_height = get_vres() / no_rectangles;

  //draws the rectangles
  for(int i = 0; i < no_rectangles; i++){
    for(int j = 0; j < no_rectangles; j++){

      //changes the color according to the rectangle position and video mode
      uint32_t color;
      if(mode == VBE_INDEXED_COLOR){
        color = (first + (i * no_rectangles + j) * step) % (1 << get_bits_per_pixel());
      }
      else{
        uint32_t red = ( ((1 << get_mode_inf().RedMaskSize) - 1) & (first >> get_mode_inf().RedFieldPosition) + j * step) % (1 << get_mode_inf().RedMaskSize);

	      uint32_t green = (((1 << get_mode_inf().GreenMaskSize) - 1) & (first >> get_mode_inf().GreenFieldPosition) + i * step) % (1 << get_mode_inf().GreenMaskSize);

	      uint32_t blue = (((1 << get_mode_inf().BlueMaskSize) - 1) & (first >> get_mode_inf().BlueFieldPosition) + (j + i) * step) % (1 << get_mode_inf().BlueMaskSize);

        color = (red << get_mode_inf().RedFieldPosition) | (green << get_mode_inf().GreenFieldPosition) | (blue << get_mode_inf().BlueFieldPosition);
      }

      //draws the rectangle
      if(vg_draw_rectangle(j * rectangle_width, i * rectangle_height, rectangle_width, rectangle_height, color) != 0){
        return EXIT_FAILURE;
      }
    }
  }

  //wait esc
  if(KBD_wait_ESC() != 0){
    return EXIT_FAILURE;
  }

  //exits the graphics mode
  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }
  

  return EXIT_SUCCESS;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  //Map the vram
  if(map_VRAM(VBE_INDEXED_COLOR) != 0){
    return EXIT_FAILURE;
  }

  //Initializes the graphics mode
  if(intialize_graphics_mode(VBE_INDEXED_COLOR) != 0){
    return EXIT_FAILURE;
  }

  if(draw_xpm(xpm, x, y) != 0){
    return EXIT_FAILURE;
  }

  //wait esc
  if(KBD_wait_ESC() != 0){
    return EXIT_FAILURE;
  }

  //exits the graphics mode
  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  //Map the vram
  if(map_VRAM(VBE_INDEXED_COLOR) != 0){
    return EXIT_FAILURE;
  }

  //Initializes the graphics mode
  if(intialize_graphics_mode(VBE_INDEXED_COLOR) != 0){
    return EXIT_FAILURE;
  }

  if(draw_xpm(xpm, xi, yi) != 0){
    return EXIT_FAILURE;
  }


  int direction = 0; //0 is horizontal 1 is vertical
  if((xi == xf) && (yi < yf)){
    direction = 1;
  }


  int nr_frames = 0;
  int displacement = 1;

  if(speed < 0){
    nr_frames = speed * (-1);
  }
  else{
    displacement = speed;
  }
 

  uint16_t x = xi;
  uint16_t y = yi;
  int c_nr_frames = nr_frames;

  int ipc_status;
  message msg;
  uint8_t timer_Mask, kbc_Mask;
  int r = 0;
  uint8_t bit_no = 0; 

  if(kbc_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }
  kbc_Mask = BIT(bit_no);

  if(timer_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }
  timer_Mask = BIT(bit_no);


  if(timer_set_frequency(0, fr_rate) != 0){
    return EXIT_FAILURE;
  }


  while((scancode != KBD_ESC_BREAK) && (x < xf || y < yf)){
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
      }

        if (is_ipc_notify(ipc_status)) { /* received notification */
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE: /* hardware interrupt notification */

                if(msg.m_notify.interrupts & kbc_Mask){
                  kbc_ih();
                }	
          			
                if (msg.m_notify.interrupts & timer_Mask) { 
                      

                      if(c_nr_frames == 0){

                        if(direction == 0){
                          x = x + displacement;
                          if(x > xf) x = xf;
                          c_nr_frames = nr_frames;

                          if(draw_xpm(xpm, x, y) != 0){
                            return EXIT_FAILURE;
                          }

                        }

                        else{
                          y = y + displacement;
                          if(y > yf) y = yf;
                          c_nr_frames = nr_frames;

                          if(draw_xpm(xpm, x, y) != 0){
                            return EXIT_FAILURE;
                          }

                        }
                        
                      }
                      else{
                          c_nr_frames--;
                        }
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */	
        }
    } else { /* received a standard message, not a notification */
        /* no standard messages expected: do nothing */
    }
  }

  if(kbc_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  if(timer_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  //exits the graphics mode
  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;

}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

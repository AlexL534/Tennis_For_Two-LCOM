// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>
#include "graphics.h"
#include "kbd.c"
#include "utils.c"
#include "i8042.h"

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

  if(vg_exit() != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}

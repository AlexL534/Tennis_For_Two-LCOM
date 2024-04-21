#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "rtc.h"
#include "kbd.h"
#include "i8042.h"
#include "xpms/Court_rec.xpm"
#include "VBE.h"
#include "video.h"

extern uint8_t scancode;

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

int (proj_main_loop)(int argc, char **argv) {
  if(map_VRAM(VBE_MODE_8888
  ) != 0){
    return EXIT_FAILURE;
  }

  //Initializes the graphics mode
  if(intialize_graphics_mode(VBE_MODE_8888) != 0){
    return EXIT_FAILURE;
  }

  if(draw_xpm((xpm_map_t) court, XPM_8_8_8_8, 0, 0) != 0){
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

  return 0;
}

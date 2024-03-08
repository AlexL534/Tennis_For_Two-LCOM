#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "kbd.h"
#include "i8042.h"
#include "timer.c"

extern uint8_t scancode;
extern uint32_t counter_KBD;
extern int counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  
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
                       kbd_print_scancode(!(scancode & KBD_BREAKCODE), (scancode == KBD_TWOBYTES) ? 2 : 1, &scancode);
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

  if(kbd_print_no_sysinb(counter_KBD) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int(kbd_test_poll)() {
  while(scancode != KBD_ESC_BREAK){
          
        kbc_ih();
        if(scancode == 0){
          continue;
        }
        kbd_print_scancode(!(scancode & KBD_BREAKCODE), (scancode == KBD_TWOBYTES) ? 2 : 1, &scancode);
  }

  if(kbc_activate() != 0){
    return EXIT_FAILURE;
  };


  if(kbd_print_no_sysinb(counter_KBD) != 0){
    return EXIT_FAILURE;
  }


  return EXIT_SUCCESS;
}

int(kbd_test_timed_scan)(uint8_t n) {
  
  uint8_t cnt = n;
  int last_counter = 0;
  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

  if(kbc_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }

  uint8_t KBD_bit = BIT(bit_no);
  if(timer_subscribe_int(&bit_no) != 0){
    return EXIT_FAILURE;
  }


  uint8_t TIMER_bit = BIT(bit_no);

  while((scancode != KBD_ESC_BREAK) && cnt){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }
         if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (msg.m_notify.interrupts & KBD_bit) { /* subscribed interrupt */
                       kbc_ih();
                       kbd_print_scancode(!(scancode & KBD_BREAKCODE), (scancode == KBD_TWOBYTES) ? 2 : 1, &scancode);
                       cnt = n;
                       last_counter = counter;
                 }
                 if(msg.m_notify.interrupts & TIMER_bit){ 
                      timer_int_handler();
                       if((counter - last_counter) % 60 == 0){
                          cnt--;
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

  if(kbd_print_no_sysinb(counter_KBD) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

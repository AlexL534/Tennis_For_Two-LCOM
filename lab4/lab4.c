// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "mouse.h"
#include "i8042.h"
#include "timer.c"
#include "state_machine.h"
#include "state_machine.c"


extern uint8_t byte_index;
extern struct packet mouse_packet;
extern int counter;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}


int (mouse_test_packet)(uint32_t cnt) {
      
  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

//enbles mouse data report
  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

//Enable mouse interrupts
  if(mouse_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }


  uint8_t irq_set = BIT(bit_no);
  while(cnt){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */    
                       mouse_ih();
                       mouse_insert_byte();
                       if(byte_index == 3){
                          mouse_insert_in_packet();
                          mouse_print_packet(&mouse_packet);
                          byte_index = 0;
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

  //Disables mouse interrupts
  if(mouse_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  //Disables mouse data report
  if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int (mouse_test_async)(uint8_t idle_time) {
  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;
  uint8_t bit_no2;
  uint8_t secs = idle_time;
  int last_counter = 0;

  //enbles mouse data report
  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  //susbcribes the interrupts for the mouse an timer, respectively
  if(mouse_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }
  if(timer_subscribe_int(&bit_no2) != 0){
    return EXIT_FAILURE;
  }

  //initializes the mouse and timer masks
  uint8_t mouse_mask = BIT(bit_no);
  uint8_t timer_mask = BIT(bit_no2);


  while(secs){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */	
                  if (msg.m_notify.interrupts & timer_mask) { 
                    //Timer nterruption
                    timer_int_handler();
                    if ((counter - last_counter) % 60 == 0){ 
                      //1 second from the previous interrupt
                      secs--;
                    }
                  }	

                 if (msg.m_notify.interrupts & mouse_mask) { //Mouse interrupt

                       mouse_ih();
                       mouse_insert_byte();
                       if(byte_index == 3){
                          mouse_insert_in_packet();
                          mouse_print_packet(&mouse_packet);
                          byte_index = 0;
                       }

                     //resets the auxiliary values
                      secs = idle_time;
                      last_counter = counter;
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */	
         }
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
}
  //unsusbcribes the interrupts for the timer an mouse, respectively
  if (timer_unsubscribe_int() != 0) {
        return EXIT_FAILURE;
  }
  if(mouse_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  //Disables mouse data report
  if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}


int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
  int ipc_status;
  message msg;
  int r = 0;
  uint8_t bit_no;

//enbles mouse data report
  if(mouse_write_byte(MOUSE_EN_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

//Enable mouse interrupts
  if(mouse_subscribe_int(&bit_no) != 0){
      return EXIT_FAILURE;
  }


  uint8_t irq_set = BIT(bit_no);
  
  //condition to exit is execute the inverted v shape
  while(get_Current_State() != END){
        if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
          printf("driver_receive failed with: %d", r);
          continue;
        }

         if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */				
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */    
                       mouse_ih();
                       mouse_insert_byte();
                       if(byte_index == 3){
                          mouse_insert_in_packet();
                          mouse_print_packet(&mouse_packet);
                          state_machine(&mouse_packet, x_len, tolerance);
                          byte_index = 0;
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

//Disables mouse interrupts
  if(mouse_unsubscribe_int() != 0){
    return EXIT_FAILURE;
  }

  //Disables mouse data report
  if(mouse_write_byte(MOUSE_DIS_DATA_REP) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}



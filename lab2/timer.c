#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t rb_command = 0;

  //Insert read_back Command
  rb_command |= TIMER_RB_CMD; // 11000000b

  //Insert count and status (their active low!!!)
  rb_command |= TIMER_RB_COUNT_; //counter to 1
  //rb_command ^= TIMER_RB_STATUS_;//status to 0

  //Insert Timer Value
  rb_command |= TIMER_RB_SEL(timer);

  //Write command on the control register
  if(sys_outb(TIMER_CTRL , rb_command) != 0){
    return EXIT_FAILURE;
  }
  //reads the value on the timer
  if(util_sys_inb(TIMER_0 + timer,st) != 0){
    return EXIT_FAILURE;
  }
  printf("value = %x\n",*st);
  return EXIT_SUCCESS;

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

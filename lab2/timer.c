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
  return EXIT_SUCCESS;

}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val conf;
  uint8_t init = 0;

  switch(field){
    //configures the entire Byte
    case tsf_all:
      conf.byte = st;
      break;

    //configures the timer's initialization mode
    case tsf_initial:
      init =  ((st << 2) >> 6) & (0x03);
      
      switch (init)
      {
      case 1:
        conf.in_mode = LSB_only;
        break;
      case 2: 
        conf.in_mode = MSB_only;
        break;
      case 3:
        conf.in_mode = MSB_after_LSB;
        break;
      default:
        conf.in_mode = INVAL_val;
        break;
      }
      
      break;

    //Configures the timer's counting mode
    case tsf_mode:
      conf.count_mode = ((st << 4) >> 5) & (0x07);
      if(conf.count_mode == 6){
        conf.count_mode = 2;
      }
      else if(conf.count_mode == 7){
        conf.count_mode = 3;
      }
      printf("%u\n",conf.count_mode);
      break;

    //Configures the timer's counting base
    case tsf_base:
      if(st & TIMER_BCD){
        conf.bcd = true;
      }
      else{
        conf.bcd = false;
      }
      break;
  }

  return timer_print_config(timer, field, conf);
}

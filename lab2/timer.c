#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

uint32_t count=0;
int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  //Get Timer configuration
  uint8_t conf = 0;
  if(timer_get_conf(timer, &conf) != 0){
    return EXIT_FAILURE;
  }

  conf &= 0x0F; //resets 4 first bits

  //Insert the timer we want to configure
  switch(timer){
    case 0:
      conf |= TIMER_SEL0;
      break;
    case 1:
      conf |= TIMER_SEL1;
      break;
    case 2:
      conf |= TIMER_SEL2;
      break;
  }

  //Insert Initialization Mode
  conf |= TIMER_LSB_MSB;


  //write command on the control register
  if(sys_outb(TIMER_CTRL, conf) != 0){
    return EXIT_FAILURE;
  }

  //calculates the div value and separates the lsb and msb
  uint16_t div = TIMER_FREQ/freq;
  uint8_t lsb = 0;
  uint8_t msb = 0;
  if(util_get_LSB(div,&lsb) != 0){
    return EXIT_FAILURE;
  }
  if(util_get_MSB(div,&msb) != 0){
    return EXIT_FAILURE;
  }

  //inserts the lsb and msb in the timer
  if(sys_outb(TIMER_0 + timer, lsb) != 0){
    return EXIT_FAILURE;
  }
  if(sys_outb(TIMER_0 + timer, msb) != 0){
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
  
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);

  /*initialize the hook_id value with the bit_no value
  Then call the sys_irqsetpolicy(int irq_line, int policy, int *hook_id)
  Use TIMER0_IRQ macro defined in the i8254.h file for the irq_line
  policy is  IRQ_REENABLE*/

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);

  /*Call the sys_irqrmpolicy(int *hook_id) where hook_id is the same as the bit_no*/

}

void (timer_int_handler)() {
  /* To be implemented by the students */
  //printf("%s is not yet implemented!\n", __func__);
  count++;
  /*Increments a global variable*/
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

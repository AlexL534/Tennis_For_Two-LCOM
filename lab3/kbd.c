#include <lcom/lcf.h>

#include "i8042.h"
#include "kbd.h"

uint8_t scancode = 0;
int hook_id = 0;
uint32_t counter_KBD = 0;

void (kbc_ih)() {
    uint8_t status = 0;
    uint8_t value = 0;

    if(kbc_read_status(&status) != 0){
        printf("Error in the status reading \n");
    }
    if(kbc_read_scancode(&value, &status) != 0){
        printf("Error in the scancode reading \n");
    }

}

int (kbc_read_status)(uint8_t *status){
    int attempts = 20; 

    while(attempts){
        if(util_sys_inb(KBC_ST_REG, status) != 0){
            return EXIT_FAILURE;
        }

        #ifdef LAB3
        counter_KBD++;
        #endif


        if(*status & KBC_OBF){
            return EXIT_SUCCESS;
        }
        tickdelay(micros_to_ticks(DELAY_US));
        attempts--;
    }

    return EXIT_FAILURE;
}

int (kbc_read_scancode)(uint8_t *value, uint8_t *status){

    if(util_sys_inb(KBC_OUT_BUF, value) != 0){
        return EXIT_FAILURE;
    }

    #ifdef LAB3
    counter_KBD++;
    #endif

    if(*status & (KBC_PARITY | KBC_TIMEOUT | KBC_AUX)){
        return EXIT_FAILURE;
    }

    scancode = *value;
    return EXIT_SUCCESS;
}

int (kbc_subscribe_int)(uint8_t *bit_no){
    *bit_no = hook_id;

    if(sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id) != 0)

        return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int (kbc_unsubscribe_int)(){
    if(sys_irqrmpolicy(&hook_id) != 0){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

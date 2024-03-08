#include <lcom/lcf.h>

#include "i8042.h"
#include "kbd.h"

uint8_t scancode = 0;
int KBD_hook_id = 0;
uint32_t counter_KBD = 0;

void (kbc_ih)() {
    uint8_t status = 0;
    uint8_t value = 0;

    if(kbc_read_status(&status) != 0){
        scancode = 0;
        printf("Error in the status reading \n");
    }
    if(kbc_read_scancode(&value, &status) != 0){
        scancode = 0;
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

        if(*status & (KBC_PARITY | KBC_TIMEOUT | KBC_AUX)){
            return EXIT_FAILURE;
    }


        if(*status & KBC_OBF){
            return EXIT_SUCCESS;
        }
        attempts--;
        tickdelay(micros_to_ticks(DELAY_US));
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

    scancode = *value;
    return EXIT_SUCCESS;
}

int (kbc_subscribe_int)(uint8_t *bit_no){
    *bit_no = IRQ_KEYBOARD; 
    KBD_hook_id = *bit_no;

    if(sys_irqsetpolicy(IRQ_KEYBOARD, IRQ_REENABLE | IRQ_EXCLUSIVE, &KBD_hook_id) != 0)

        return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int (kbc_unsubscribe_int)(){
    if(sys_irqrmpolicy(&KBD_hook_id) != 0){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int(kbc_activate)(){
    uint8_t command = KBC_RD_CM_B;

    if(kbc_read_command(&command) != 0){
        return EXIT_FAILURE;
    }

    command = KBC_WRT_CM_B;
    if(kbc_write_command(&command, KBC_ST_REG)!= 0){
        return EXIT_FAILURE;
    }

    command |= KBD_ENABLE;


    if(kbc_write_command(&command, KBC_OUT_BUF) != 0){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int(kbc_read_command)(uint8_t *command){

   if(kbc_write_command(command,KBC_CMD_REG) != 0){
    return EXIT_FAILURE;
   }

   if(util_sys_inb(KBC_OUT_BUF, command) != 0){
    return EXIT_FAILURE;
   }

    #ifdef LAB3
    counter_KBD++;
    #endif

    return EXIT_SUCCESS;
}


int(kbc_write_command)(uint8_t *command, int port){
    uint8_t status = 0;
    while( 1 ) {
        if(util_sys_inb(KBC_ST_REG, &status) != 0){
            return EXIT_FAILURE;
        }
        #ifdef LAB3
        counter_KBD++;
        #endif
        /* loop while 8042 input buffer is not empty */
        if(status & (KBC_PARITY | KBC_TIMEOUT | KBC_AUX)){
            return EXIT_FAILURE;
        }
        if( (status & KBC_OBF) == 0 ) {
            sys_outb(port, *command); /* no args command */
            return EXIT_SUCCESS;
        }
        tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
    }
}

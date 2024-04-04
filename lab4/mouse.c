#include "mouse.h"
#include "i8042.h"

int hook_id_mouse = 0;
uint8_t byte_index = 0;      
uint8_t mouse_bytes[3];       
uint8_t current_byte;
struct packet mouse_packet;



void (mouse_ih)(){

  //handles the mouse interrupts
  if(mouse_read_byte() != 0){
    printf("Error in the byte reading \n");
    current_byte = 0;
  }

}

int (mouse_read_status)(uint8_t *status){

    //Reads the status at the status register
    if(util_sys_inb(KBC_ST_REG, status) != 0){
          return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int (mouse_read_byte)(){
    uint8_t value = 0;
    uint8_t status = 0;
    uint8_t maxIterations = 20; //maximum number of iterations that the loop will contain (avoids the program to block)

    while(maxIterations){
      //reads the status
      if(mouse_read_status(&status) != 0){
        return EXIT_FAILURE;
      }

      //checks if there was an error
      if(status & (KBC_PARITY | KBC_TIMEOUT)){
            return EXIT_FAILURE;
      }

      //checks if the output buffer is full and the byte is the mouse
      if((status & KBC_OBF) && (status & KBC_AUX)) {
        
        //Reads the byte
        if(util_sys_inb(KBC_OUT_BUF, &value) != 0){
          return EXIT_FAILURE;
        }

        current_byte = value;
        return EXIT_SUCCESS;
      }

      //Waits enough time until trying again
        tickdelay(micros_to_ticks(DELAY_US));
        maxIterations--;
    }

    return EXIT_FAILURE;
  
}

int (mouse_subscribe_int)(uint8_t *bit_no){
    *bit_no = 2;  
    hook_id_mouse = *bit_no;

    if(sys_irqsetpolicy(IRQ_MOUSE, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse) != 0)
        return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

int (mouse_unsubscribe_int)(){
    if(sys_irqrmpolicy(&hook_id_mouse) != 0){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}


void (mouse_insert_byte)(){

  //checks if the bit 3 (mouse control byte) is active and if the current index is 0 (new byte)
  if(byte_index == 0 && (current_byte & MOUSE_CONTROL)){
    mouse_bytes[byte_index] = current_byte;
    byte_index++;
  }

  else if(byte_index > 0){
    mouse_bytes[byte_index] = current_byte;
    byte_index++;
  }
}

int (mouse_write_command)(uint8_t command, int port){
  uint8_t status = 0;
  uint8_t maxIterations = 20; //maximum number of iterations that the loop will contain (avoids the program to block)

    while( maxIterations ) {
        if(mouse_read_status(&status) != 0){
          return EXIT_FAILURE;
        }

        //checks if there wasn't any error
        if(status & (KBC_PARITY | KBC_TIMEOUT)){
            return EXIT_FAILURE;
        }

        //cheks if the the input buffer is empty
        if(((status & KBC_IBF)) == 0 ) {
          //write the command
            sys_outb(port, command); 
            return EXIT_SUCCESS;
        }

        //waits enough time until trying again
        tickdelay(micros_to_ticks(DELAY_US)); // e.g. tickdelay()
        maxIterations--;
    }

    return EXIT_FAILURE;

}

void (mouse_insert_in_packet)(){

  //writes the 3 bytes into the packt
  for(int i = 0; i < 3; i++){
    mouse_packet.bytes[i] = mouse_bytes[i];
  }

  //fills the rest of the areas with the apropriate value
  mouse_packet.lb = mouse_bytes[0] & MOUSE_LB;
  mouse_packet.mb = mouse_bytes[0] & MOUSE_MB;
  mouse_packet.rb = mouse_bytes[0] & MOUSE_RB;

  //check if x value is negative (2's complement) and inserts 1 if so
  mouse_packet.delta_x = (mouse_bytes[0] & MOUSE_MSB_X) ? (0xFF00 | mouse_bytes[1]) : mouse_bytes[1]; 
  mouse_packet.delta_y = (mouse_bytes[0] & MOUSE_MSB_Y) ? (0xFF00 | mouse_bytes[2]) : mouse_bytes[2];

  //fills the rest of the areas with the apropriate value
  mouse_packet.x_ov = mouse_bytes[0] & MOUSE_X_OVF;
  mouse_packet.y_ov = mouse_bytes[0] &  MOUSE_Y_OVF;

}

int (mouse_write_byte)(uint8_t command){
  uint8_t return_byte = 0;
  int maxIterations = 20;
  while(maxIterations){

    //0xD4 commands the KBC to forward its argument to the mouse without any interpretation
    if(mouse_write_command(MOUSE_WRITE_BYTE,KBC_CMD_REG) != 0){
      return EXIT_FAILURE;
    }

    //writes the arguments to the mouse
    if(mouse_write_command(command,KBC_OUT_BUF) != 0){
      return EXIT_FAILURE;
    }

    //waits a bit so that the mouse can receive an process the commands
    tickdelay(micros_to_ticks(DELAY_US));

    //read the response from the mouse
    if(util_sys_inb(KBC_OUT_BUF, &return_byte) != 0){
      return EXIT_FAILURE;
    }
    
    //if is ACK (everything ok) exit the loop
    if(return_byte == MOUSE_ACK){
      return EXIT_SUCCESS;
    }

    maxIterations--;
  }


  return EXIT_SUCCESS;
}

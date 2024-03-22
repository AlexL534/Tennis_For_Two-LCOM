#include "state_machine.h"

static v_states current_state = INITIAL;
static uint16_t current_len = 0;

v_states (get_Current_State)(){
  return current_state;
}

//Verifies if the tolerance is respect
bool (verify_tolerance)(int16_t x_delta, int16_t y_delta, uint8_t tolerance){
  switch(current_state){

    case FIRST_LINE:
      if((x_delta < 0 - tolerance) || (y_delta < 0 - tolerance)){
        return false;
      }
      break;


    case SECOND_LINE:
      if((x_delta < 0 -tolerance) || (y_delta > 0 - tolerance))
        return false;
      break;

    case VERTEX:
      if(x_delta > tolerance || y_delta > tolerance || y_delta < 0 - tolerance || x_delta < 0 - tolerance)
        return false;
      break;
    
    default:
    break;
    //does nothing in other cases
  }

  return true;
}

//verifies if the slope is bigger than the module of 1
bool (verify_slope)(int16_t x_delta, int16_t y_delta){
  switch(current_state){

    case FIRST_LINE:
      if((x_delta >= y_delta))
        return false;
      break;

    case SECOND_LINE:
      if(x_delta * (-1) <= y_delta)
        return false;
      break;
    
    default:
    break;
    //does nothing in other cases

  }

  return true;
}

//verifies if the x_len was reached
bool (verify_x_len)(int16_t x_len){
  return x_len <= current_len;
}

//implementation of the state machine
void (state_machine)(struct packet *mouse_packet, int16_t x_len, uint8_t tolerance){
  current_len += mouse_packet->delta_x;

  switch(current_state){

    case INITIAL:
      if(mouse_packet->lb)
        current_state = FIRST_LINE;
      break;

    case FIRST_LINE:
      if(!mouse_packet->lb || mouse_packet->rb || mouse_packet->mb){
        current_state = INITIAL;
        break;
      }

      if(!verify_tolerance(mouse_packet->delta_x, mouse_packet->delta_y, tolerance)){
        current_state = INITIAL;
        break;
      }

      if(!verify_slope(mouse_packet->delta_x, mouse_packet->delta_y)){
        current_state = INITIAL;
        break;
      }

      if(verify_x_len(x_len)){
         if(!mouse_packet->lb){
          current_state = END;
          current_len = 0;
        }
        current_state = VERTEX;
        current_len = 0;
        break;
      }
      break;
    
    case VERTEX:
      if(mouse_packet->rb){
        current_state = SECOND_LINE;
        current_len = 0;
        break;
      }

      if(mouse_packet->lb || mouse_packet->mb){
        current_state = INITIAL;
        break;
      }

      if(!verify_tolerance(mouse_packet->delta_x, mouse_packet->delta_y, tolerance)){
        current_state = INITIAL;
        break;
      }
      break;
    
    case SECOND_LINE:
      if(verify_x_len(x_len)){
        if(!mouse_packet->rb){
        current_state = END;
        current_len = 0;
        }
                break;
      }
      if(mouse_packet->lb || !mouse_packet->rb || mouse_packet->mb){
        current_state = INITIAL;
        break;
      }

      if(!verify_tolerance(mouse_packet->delta_x, mouse_packet->delta_y, tolerance)){
        current_state = INITIAL;
        break;
      }

      if(!verify_slope(mouse_packet->delta_x, mouse_packet->delta_y)){
        current_state = INITIAL;
        break;
      }

      break;
    
    default:
    break;
    //does nothing in other case

  }

}

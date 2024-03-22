#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include <lcom/lcf.h>

typedef enum {INITIAL, FIRST_LINE, VERTEX, SECOND_LINE, END} v_states;

void (state_machine)(struct packet *mouse_packet, int16_t x_len, uint8_t tolerance);
bool (verify_tolerance)(int16_t x_delta, int16_t y_delta, uint8_t tolerance);
bool (verify_slope)(int16_t x_delta, int16_t y_delta);
bool (verify_x_len)(int16_t x_len);
v_states (get_Current_State)();





#endif

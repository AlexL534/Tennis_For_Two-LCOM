#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <lcom/lcf.h>

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
int (mouse_read_status)();
int (mouse_read_byte)();
int (mouse_write_byte)(uint8_t command);
int (mouse_write_command)(uint8_t command, int port);
void (mouse_ih)();
void (mouse_insert_byte)();
void (mouse_insert_in_packet)();

#endif

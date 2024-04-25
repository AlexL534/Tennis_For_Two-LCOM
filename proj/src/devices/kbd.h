#ifndef KBD_H
#define KBD_H
#include <lcom/lcf.h>

int (kbd_read_status)(uint8_t *status);
int (kbd_read_scancode)();
int (kbd_subscribe_int)(uint8_t *bit_no);
int (kbd_unsubscribe_int)();
int(kbd_activate)();
int(kbd_read_command)(uint8_t *command);
int(kbd_write_command)(uint8_t *command, int port);
uint8_t (get_scancode)();
int (get_KBD_hook_id)();

#endif

#include <lcom/lcf.h>

int (kbc_read_status)(uint8_t *status);
int (kbc_read_scancode)();
int (kbc_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();
int(kbc_activate)();
int(kbc_read_command)(uint8_t *command);
int(kbc_write_command)(uint8_t *command, int port);

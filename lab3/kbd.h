#include <lcom/lcf.h>

int (kbc_read_status)(uint8_t *status);
int (kbc_read_scancode)(uint8_t *value, uint8_t *status);
int (kbc_subscribe_int)(uint8_t *bit_no);
int (kbc_unsubscribe_int)();

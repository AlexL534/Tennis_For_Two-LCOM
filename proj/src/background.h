#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <lcom/lcf.h>

int (drawBackground)(uint32_t *background);
int (drawPortionOfBackground)(uint32_t *background, uint16_t x, uint16_t y, uint16_t widht, uint16_t height);

#endif

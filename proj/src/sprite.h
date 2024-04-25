#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
typedef struct {
  int width, height; // dimensions
  uint32_t *map; // the pixmap
} Sprite;

#endif

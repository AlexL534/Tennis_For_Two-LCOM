#ifndef SPRITE_H
#define SPRITE_H

#include <lcom/lcf.h>
/**
 * @struct Sprite
 * @brief Estrutura que contem as informações esseciais de cada sprite
 * @var Sprite::width
 * Comprimento do Sprite
 * @var Sprite::height
 * Altura do sprite
 * @var map
 * Pixmap do sprite
*/
typedef struct {
  int width, height; // dimensions
  uint32_t *map; // the pixmap
} Sprite;

#endif

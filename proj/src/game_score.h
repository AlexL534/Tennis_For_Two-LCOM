#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include <lcom/lcf.h>
#include "xpms.h"
#include "sprite.h"
#include "color.h"

int (loadInitialXPMScore)();
int (drawScore)(int playerNumb);
int (updateXPMScore)(int playerNumb, int score);
void (chooseXPMScore)(int score, uint32_t *xpm, xpm_image_t *img);
void (freeXPMScore)();

#endif
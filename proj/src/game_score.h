#ifndef GAME_SCORE_H
#define GAME_SCORE_H

#include <lcom/lcf.h>
#include "xpms.h"
#include "devices/video.h"
#include "sprite.h"
#include "color.h"

/**
 * Inicia as estruturas que vão conter os sprites usados no quadro de pontuações
 * @returns 1 se ocorreu algum erro ou zero caso tenha corrido tudo bem
*/
int (loadInitialXPMScore)();
int (drawScore)(int playerNumb);
int (drawScoreText)();
int (updateXPMScore)(int playerNumb, int score);
void (chooseXPMScore)(int score, Sprite *scoreSprite);
void (freeXPMScore)();

#endif

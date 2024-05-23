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

/**
 * Desenha no ecrã as pontuações no quadro de pontuações.
 * @param playerNumb Número do jogador que queremos desenhar a pontuação
 * @returns 1 se ocorreu algum erro ou zero caso tenha corrido tudo bem
 * 
*/
int (drawScore)(int playerNumb);

/**
 * Desenha o texto que aparece antes das pontuações e que permite distinguir as pontuações do player 1 e 2
 * @returns 1 se ocorreu algum erro ou zero caso tenha corrido tudo bem
*/
int (drawScoreText)();

/**
 * Atualiza o XPM a usar tendo em conta a nova pontuação de um certo jogador
 * @param playerNumb Número do jogador que vai ter um novo XPM para a sua pontução
 * @param score Nova pontuação
 * @returns 1 se ocorreu algum erro ou zero caso tenha corrido tudo bem
*/
int (updateXPMScore)(int playerNumb, int score);

/**
 * Escolhe a XPM a carregar tendo em conta a pontuação fornecida
 * @param score Pontuação
 * @param scoreSprite Sprite que vamos atualizar com o novo pixmap carregado do XPM
*/
void (chooseXPMScore)(int score, Sprite *scoreSprite);

/**
 * Liberta a memória alocada para os Sprites das pontuações
*/
void (freeXPMScore)();

#endif

#ifndef PLAYER2_H
#define PLAYER2_H

#include "player.h"
#include "ball.h"
#include "devices/i8042.h"
#include "devices/video.h"

/**
 * Atualiza os movimentos/estados/animações do jogador 2 tendo em conta as informações da bola (posição, direção de movimento, ...) quando estamos e jogar em single player
 * @param player2 Jogador 2 que vamos atualizar
 * @param ball bola que vamos usar como referencia
 * @param counter Valor do counter atualizado pelo timer
 * @param canHitAfterServe Indica se é permitido ao player acertar na bola depois do serviço
*/
void updatePlayer2AI(Player *player2, Ball *ball, int counter, bool canHitAfterServe);

#endif // PLAYER2_H

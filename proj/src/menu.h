#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include "states.h"
#include "sprite.h"
#include "player.h"

#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"
#include "xpms.h"

/**
 * @struct Mouse
 * @brief Estrutura que contém as coordenadas e o sprite do mouse
 */
typedef struct {
    Sprite* sprite; /**< Apontador para o sprite do mouse. */
    int x;          /**< Coordenada x do mouse. */
    int y;          /**< Coordenada y do mouse. */
} Mouse;

/**
 * @brief Cria um objeto Mouse.
 * @return Retorna um apontador para o Mouse.
 */
Mouse* createMouse();

/**
 * @brief Desenha o mouse na tela.
 * @param mouse Apontador para o objeto Mouse a ser desenhado.
 * @return Retorna 1 se ocorreu algum erro e 0 se correu tudo bem
 */
int drawMouse(Mouse* mouse);

/**
 * @brief Destrói um objeto Mouse.
 * @param mouse Apontador para o objeto Mouse a ser destruído.
 */
void destroyMouse(Mouse* mouse);

/**
 * @brief Atualiza a posição do mouse.
 * @param mouse Apontador para o objeto Mouse a ser atualizado.
 * @param delta_x Mudança na coordenada x.
 * @param delta_y Mudança na coordenada y.
 * @return Retorna 1 se ocorreu algum erro e 0 se correu tudo bem
 */
int updateMousePosition(Mouse* mouse, int delta_x, int delta_y);

#endif

#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "sprite.h"
#include <lcom/lcf.h>
#include "xpms.h"
#include "player.h"
#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"


typedef struct{
    Game_state state;
    Sprite title;
    Sprite play_button;
    Sprite quit;
    Sprite play_button_hover;
    Sprite quit_hover;
    uint8_t selected;

}Menu;

Menu* (initialize_menu)();
int (menu_loop)();
int (kbdhandler)();
int (update_selected)(unsigned char code);
int (timehandler)();
Game_state (get_state)();
int (menu_destroyer)();
int (draw_field)(int x_offset, int y_offset, Sprite sprite);
int clear_screen();
int (draw_menu)();
int (draw_date)(uint8_t day, uint8_t month, uint8_t year);
int (choose_number_sprite)(uint8_t num, Sprite* sprite);



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

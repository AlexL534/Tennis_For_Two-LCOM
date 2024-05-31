#ifndef MENU_H
#define MENU_H

#include <lcom/lcf.h>
#include "states.h"
#include "sprite.h"
#include "xpms.h"
#include "player.h"
#include "game.h"
#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"


typedef struct{
    Sprite title;
    Sprite play_button;
    Sprite quit;
    Sprite play_button_hover;
    Sprite quit_hover;
    Sprite pause_menu;
    Sprite resume;
    Sprite restart;
    Sprite quit_pause;
    Sprite resume_hover;
    Sprite restart_hover;
    Sprite quit_pause_hover;
    uint8_t selected;
} Menu;

/**
 * @struct Mouse
 * @brief Estrutura que contém as coordenadas e o sprite do mouse
 */
typedef struct {
    Sprite* sprite; /**< Apontador para o sprite do mouse. */
    int x;          /**< Coordenada x do mouse. */
    int y;          /**< Coordenada y do mouse. */
} Mouse;

Menu* (initialize_menu)(bool isStartMenu);
int (kbd_handler_menu)(Game_state* state, Menu* menu);
int (update_selected)(unsigned char code, Game_state* state, Menu* menu);
int (time_handler_menu)(Menu* menu, Mouse* mouse);
int (draw_field)(int x_offset, int y_offset, Sprite sprite);
int (clear_screen)();
int (draw_menu)(Menu* menu);
int (draw_date)(uint8_t day, uint8_t month, uint8_t year);
int (choose_number_sprite)(uint8_t num, Sprite* sprite);

int update_selected_pause(unsigned char code, Game_state* game_state, Menu* menu);
int drawPause(Menu *menu);

void update_selected_mouse(Menu* menu, Mouse* mouse, bool isStartMenu);


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

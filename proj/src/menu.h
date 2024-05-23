#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "sprite.h"
#include <lcom/lcf.h>
#include "xpms.h"

typedef struct{
    Game_state state;
    Sprite title;
    Sprite play_button;
    Sprite quit;
    uint8_t selected;

}Menu;

int (initialize_menu)();
int (start_game)();
int (quit_game)();
int (draw_field)(int offset);
#endif
#ifndef MENU_H
#define MENU_H

#include "states.h"
#include "sprite.h"

typedef struct{
    Game_state state;
    Sprite title;
    Sprite play_button;
    Sprite quit;

}Menu;


int start_game();
int quit_game();
#endif
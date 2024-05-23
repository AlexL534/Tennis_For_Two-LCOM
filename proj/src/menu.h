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
    uint8_t selected;

}Menu;

int (initialize_menu)();
int (start_game)();
int (quit_game)();
int (draw_field)(int offset);



typedef struct {
    Sprite* sprite; 
    int x; 
    int y; 
} Mouse;

Mouse* createMouse();

int drawMouse(Mouse* mouse);

void destroyMouse(Mouse* mouse);

int updateMousePosition(Mouse* mouse, int delta_x, int delta_y);

#endif

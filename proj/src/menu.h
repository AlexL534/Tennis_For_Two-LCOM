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
int (draw_menu)();



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

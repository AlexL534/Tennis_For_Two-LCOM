#ifndef PAUSE_H
#define PAUSE_H

#include "states.h"
#include "sprite.h"
#include <lcom/lcf.h>
#include "xpms.h"
#include "player.h"
#include "menu.h"
#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"


typedef struct{
    Game_state state;
    Sprite pause_menu;
    Sprite resume;
    Sprite restart;
    Sprite quit;
    Sprite resume_hover;
    Sprite restart_hover;
    Sprite quit_hover;
    uint8_t selected;

}Pause;

Pause* (initialize_pause)();
int (pause_loop)();
int (kbdhandler)();
int (update_selected_pause)(unsigned char code);
int (timehandler)();
Game_state (get_state)();
int (pause_destroyer)();
int (draw_pause)();

#endif

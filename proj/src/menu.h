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

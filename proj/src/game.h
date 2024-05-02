#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "states.h"
#include "player.h"

#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"
#include "xpms.h"


int (gameLoop)();
int (timerHandler)();
int (keyboardHandler)();
int (mouseHandler)();

void (destroyElements)();
int (loadBackground)();


#endif

#ifndef GAME_H
#define GAME_H

#include <lcom/lcf.h>
#include "states.h"
#include "player1.h"

#include "devices/i8042.h"
#include "devices/i8254.h"
#include "devices/kbd.h"
#include "devices/mouse.h"
#include "devices/rtc.h"
#include "devices/VBE.h"
#include "devices/video.h"
#include "xpms.h"


int (gameLoop)();
void (timerHandler)();
void (keyboardhandler)();

void (destroyElements)();
int (loadBackground)();


#endif

#ifndef PLAYER2_H
#define PLAYER2_H

#include "player.h"
#include "ball.h"
#include "devices/i8042.h"
#include "devices/video.h"

void updatePlayer2AI(Player *player2, Ball *ball, int counter);

#endif // PLAYER2_H

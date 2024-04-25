#ifndef PLAYER1_H
#define PLAYER1_H

#include "states.h"
#include <lcom/lcf.h>
#include "xpms.h"
#include "sprite.h"

typedef struct{
  int x, y;

  int xspeed, yspeed;

  Sprite currentSprite;
  bool isHitting;
  bool isStarting;

  Sprite move[2];
  Sprite moverev[2];

  Player_direction direction;

} Player1;

Player1 *(createPlayer1)();
int (drawPlayer1)(Player1 *player1);
void (updateDirection)(Player_direction direction, Player1 *player);
void (movePlayer1)(Player1 *player, Player_movement movement);
void (moveAnim1)(Player1 *player1);
void (destroyPlayer1)(Player1 *player1);



#endif

#ifndef PLAYER1_H
#define PLAYER1_H

#include "states.h"
#include <lcom/lcf.h>
#include "xpms.h"
#include "sprite.h"

#define MIN_X  0   
#define MAX_X  1152
#define MIN_Y  432-145 //player height is 150
#define MAX_Y  864

typedef struct{
  int x, y;

  int xspeed, yspeed;
  unsigned int moveanim;

  Sprite currentSprite;
  bool isHitting;
  bool isStarting;

  Sprite move[2];
  Sprite moverev[2];
  Sprite hit[4];
  Sprite hitrev[4];
  Sprite start[6];
  Sprite startrev[6];

  Player_direction direction;

} Player1;

Player1 *(createPlayer1)();
int (drawPlayer1)(Player1 *player1);
void (updateDirection)(Player_direction direction, Player1 *player);
void (movePlayer1)(Player1 *player, Player_movement movement);
void (moveAnim1)(Player1 *player1);
void (destroyPlayer1)(Player1 *player1);



#endif

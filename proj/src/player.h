#ifndef PLAYER_H
#define PLAYER_H

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
  unsigned int moveanim, hitanim, startanim;

  Sprite currentSprite;

  Sprite move[2];
  Sprite moverev[2];
  Sprite hit[4];
  Sprite hitrev[4];
  Sprite start[6];
  Sprite startrev[6];

  Player_direction direction;

} Player;

Player *(createPlayer)();
int (drawPlayer)(Player *player1);
void (updateDirection)(Player_direction direction, Player *player);
void (movePlayer)(Player *player, Player_movement movement);
void (moveAnim)(Player *player1);
void (hitAnim)(Player *player1);
void (startAnim)(Player *player1);
void (chooseStartAnim)(Player *player1);
void (destroyPlayer)(Player *player1);



#endif

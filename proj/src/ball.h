#ifndef BALL_H
#define BALL_H

#include "states.h"
#include <lcom/lcf.h>
#include "xpms.h"
#include "sprite.h"
#include "player.h"

typedef struct{
  int x, y;

  int xspeed, yspeed;
  int incline;

  Sprite currentSprite;

  Sprite small;
  Sprite medium;
  Sprite large;
  Sprite very_large;

  Ball_direction direction;

} Ball;

Ball *(createBall)();
int (drawBall)(Ball *ball);
void (updateBallDirection)(Ball_direction direction, Ball *ball);
void (collisionPlayer)(Ball *ball, Player *player);
void (moveBall)(Ball *ball);
bool (checkCollisionLine)(Ball *ball, uint32_t *backgorund);
void (resetBall)(Ball *ball, Player_numb scoredPlayer);
void (destroyBall)(Ball *ball);


#endif

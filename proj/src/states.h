#ifndef STATES_H
#define STATES_H

typedef enum{
  GAME,
  START_MENU,
  PAUSE_MENU
} Game_state;

typedef enum {
  LEFTD,
  RIGHTD
} Player_direction;

typedef enum{
  LEFT_PLAYER,
  RIGHT_PLAYER,
  UP_PLAYER,
  DOWN_PLAYER
} Player_movement;

typedef enum {
  MOVE,
  START,
  CHOOSE_START,
  CHOOSE_START_STOP,
  HIT,
  STOP
} Player_state;

typedef enum {
  UP_BALL,
  DOWN_BALL
} Ball_direction;

#endif

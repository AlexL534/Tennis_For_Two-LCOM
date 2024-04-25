#ifndef STATES_H
#define STATES_H

typedef enum{
  GAME,
  START_MENU,
  PAUSE_MENU
} Game_state;

typedef enum {
  LEFT,
  RIGHT
} Player_direction;

typedef enum {
  MOVE,
  START,
  HIT,
  STOP
} Player_state;

typedef enum {
  UP,
  DOWN
} Ball_direction;


#endif

#ifdef STATES_H
#define STATES_H

enum Game_state{
  GAME,
  START_MENU,
  PAUSE_MENU
}

enum Player_direction{
  LEFT,
  RIGHT
};

enum Player_state{
  MOVE,
  START,
  HIT,
};

enum Ball_direction{
  UP,
  DOWN
}


#endif
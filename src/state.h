#ifndef STATE_H
#define STATE_H

#include "graphics/renderer.h"
#include "graphics/window.h"
#include "game/game.h"

typedef enum game_state {
  MAIN_MENU, PLAYING
} game_state_t;

typedef struct state {
  game_t game;
  renderer_t renderer;
  window_t* window;
  game_state_t game_state;
} state_t;

extern state_t state;

#endif // STATE_H

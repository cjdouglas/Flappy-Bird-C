#include <stdlib.h>
#include <time.h>

#include "game/game.h"
#include "graphics/graphics.h"
#include "graphics/renderer.h"
#include "graphics/window.h"
#include "state.h"

state_t state;

static void _init() {
  state.window = &window;
  state.game_state = MAIN_MENU;
  game_init(&state.game);
  renderer_init(&state.renderer, state.game.bird, state.game.pipes, N_PIPES);
  renderer_init_cam(&state.renderer, 0.0f, state.window->w, state.window->h,
                    0.0f, 1.0f, -1.0f);
}

static void _destroy() {
  renderer_destroy(&state.renderer);
  game_destroy(&state.game);
}

static void _render() {
  renderer_draw(&state.renderer);
}

int main(int argc, char** argv) {
  time_t t;
  srand((unsigned)time(&t));
  window_create(_init, _destroy, _render);
  window_mainloop();

  return 0;
}

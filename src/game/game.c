#include "game.h"

#include <stdlib.h>

#include "../state.h"

#define MIN_HEIGHT 50
#define MAX_HEIGHT 350
#define SPAWN_RATE 1.33f

static int _next_rand() {
  return rand() % (MAX_HEIGHT + 1 - MIN_HEIGHT) + MIN_HEIGHT;
}

void game_init(game_t* self) {
  self->bird = bird_create();
  self->pipes = malloc(N_PIPES * sizeof(pipes_t));
  for (int i = 0; i < N_PIPES; ++i) {
    self->pipes[i] = pipes_create();
  }
  self->cycle_time = 0.0f;
  self->cycle_index = 0;
}

void game_update(game_t* self, float dt) {
  if (state.game_state == MAIN_MENU) {
    // TODO: add some kind of update here?
    return;
  }

  if (state.game_state == PLAYING) {
    self->cycle_time += dt;
    if (self->cycle_time >= SPAWN_RATE) {
      pipes_reset(self->pipes[self->cycle_index], 400, _next_rand());
      self->cycle_index = (self->cycle_index + 1) % N_PIPES;
      self->cycle_time = 0.0f;
    }
    bird_update(self->bird, dt);
    for (int i = 0; i < N_PIPES; ++i) {
      pipes_update(self->pipes[i], dt);
    }
    return;
  }
}

void game_input(game_t* self, int key) {
  if (key == GLFW_KEY_SPACE) {
    if (state.game_state == MAIN_MENU) {
      state.game_state = PLAYING;
    }
    bird_flap(self->bird);
  }
}

void game_destroy(game_t* self) {
  for (int i = 0; i < N_PIPES; ++i) {
    free(self->pipes[i]);
  }
  free(self->bird);
}

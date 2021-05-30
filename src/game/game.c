#include "game.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../state.h"

state_t state;

#define MIN_HEIGHT 50
#define MAX_HEIGHT 350
#define SPAWN_RATE 1.33f

static int _next_rand() {
  return rand() % (MAX_HEIGHT + 1 - MIN_HEIGHT) + MIN_HEIGHT;
}

static bool _collides(const bird_t* b, const pipes_t* p) {
  if (b->position[0] < p->position_bottom[0] + p->size_bottom[0] &&
      b->position[0] + b->size[0] > p->position_bottom[0] &&
      b->position[1] < p->position_bottom[1] + p->size_bottom[1] &&
      b->position[1] + b->size[1] > p->position_bottom[1]) {
    return true;
  }
  // Writing the block twice to avoid a HUGE conditional check
  if (b->position[0] < p->position_top[0] + p->size_top[0] &&
      b->position[0] + b->size[0] > p->position_top[0] &&
      b->position[1] < p->position_top[1] + p->size_top[1] &&
      b->position[1] + b->size[1] > p->position_top[1]) {
    return true;
  }

  return false;
}

static void _check_collisions(game_t* self) {
  const bird_t* b = self->bird;
  if (b->position[1] <= 0 || b->position[1] + BIRD_HEIGHT >= state.window->h) {
    state.game_state = DEAD;
  }

  for (size_t i = 0; i < N_PIPES; ++i) {
    if (_collides(b, self->pipes[i])) {
      state.game_state = DEAD;
    }
  }
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

  if (state.game_state == LIVE) {
    _check_collisions(self);

    self->cycle_time += dt;
    if (self->cycle_time >= SPAWN_RATE) {
      pipes_set(self->pipes[self->cycle_index], 400, _next_rand());
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
      state.game_state = LIVE;
      self->cycle_time = SPAWN_RATE / 2.0f;
    }
    bird_flap(self->bird);
    return;
  }

  if (key == GLFW_KEY_R) {
    if (state.game_state == DEAD) {
      bird_reset(self->bird);
      for (int i = 0; i < N_PIPES; ++i) {
        pipes_reset(self->pipes[i]);
      }
      state.game_state = MAIN_MENU;
    }
  }
}

void game_destroy(game_t* self) {
  for (int i = 0; i < N_PIPES; ++i) {
    free(self->pipes[i]);
  }
  free(self->bird);
}

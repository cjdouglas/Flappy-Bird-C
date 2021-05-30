#include "game.h"

#include "../entity/bird.h"

void game_init(game_t* self) {
  self->bird = bird_create();
  self->pipe = pipe_create();
}

void game_update(game_t* self, float dt) {
  bird_update(self->bird, dt);
  pipe_update(self->pipe, dt);
}

void game_input(game_t* self, int key) {
  if (key == GLFW_KEY_SPACE) {
    bird_flap(self->bird);
  }
}

void game_destroy(game_t* self) {
  free(self->bird);
}

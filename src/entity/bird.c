#include "bird.h"

#include <cglm/affine.h>
#include <stdlib.h>

#define X_START 60
#define Y_START 300
#define GRAVITY 30

static void _set_model_mat(bird_t* self) {
  glm_mat4_identity(self->model);
  glm_translate(self->model,
                (vec3){self->position[0], self->position[1], 0.0f});
  glm_scale(self->model, (vec3){self->size[0], self->size[1], 1.0f});
}

bird_t* bird_create() {
  bird_t* self = (bird_t*)malloc(sizeof(bird_t));
  bird_reset(self);
  _set_model_mat(self);
  return self;
}

void bird_flap(bird_t* self) {
  self->velocity = -9.0f;
}

void bird_update(bird_t* self, float dt) {
  self->velocity += self->acceleration * dt;
  self->position[1] += self->velocity;
  _set_model_mat(self);
}

void bird_reset(bird_t* self) {
  glm_vec2((float[2]){X_START, Y_START - (BIRD_WIDTH / 2.0f)}, self->position);
  glm_vec2((float[2]){BIRD_WIDTH, BIRD_HEIGHT}, self->size);
  self->velocity = 0.0f;
  self->acceleration = GRAVITY;
  _set_model_mat(self);
}

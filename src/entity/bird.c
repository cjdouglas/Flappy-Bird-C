#include "bird.h"

#include <cglm/affine.h>
#include <stdlib.h>

#define X_START 60
#define Y_START 300
#define GRAVITY 30

bird_t* bird_create() {
  bird_t* self = (bird_t*)malloc(sizeof(bird_t));
  glm_vec2((float[2]){X_START, Y_START - (BIRD_WIDTH / 2.0f)}, self->position);
  glm_vec2((float[2]){BIRD_WIDTH, BIRD_HEIGHT}, self->size);
  self->velocity = 0.0f;
  self->acceleration = GRAVITY;

  return self;
}

void bird_flap(bird_t* self) {
  self->velocity = -6.9f;
}

void bird_update(bird_t* self, float dt) {
  // Update position
  self->velocity += self->acceleration * dt;
  self->position[1] += self->velocity;

  // Build model matrix
  glm_mat4_identity(self->model);
  glm_translate(self->model,
                (vec3){self->position[0], self->position[1], 0.0f});
  glm_scale(self->model, (vec3){self->size[0], self->size[1], 1.0f});
}

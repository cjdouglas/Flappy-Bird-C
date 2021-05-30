#include "pipes.h"

#include <cglm/affine.h>

#include "../state.h"

pipes_t* pipes_create() {
  pipes_t* self = malloc(sizeof(pipes_t));
  pipes_reset(self, -100, 0);
  return self;
}

void pipes_reset(pipes_t* self, const float x0, const float height) {
  glm_vec2((float[2]){PIPE_WIDTH, height}, self->size_bottom);
  glm_vec2((float[2]){PIPE_WIDTH, state.window->h - PIPE_GAP - height},
           self->size_top);

  glm_vec2((float[2]){x0, 0}, self->position_bottom);
  glm_vec2((float[2]){x0, height + PIPE_GAP}, self->position_top);
}

void pipes_update(pipes_t* self, float dt) {
  self->position_bottom[0] -= PIPE_VELOCITY * dt;
  self->position_top[0] -= PIPE_VELOCITY * dt;

  glm_mat4_identity(self->model_bottom);
  glm_translate(self->model_bottom, (vec3){self->position_bottom[0],
                                           self->position_bottom[1], 0.0f});
  glm_scale(self->model_bottom,
            (vec3){self->size_bottom[0], self->size_bottom[1], 1.0f});

  glm_mat4_identity(self->model_top);
  glm_translate(self->model_top,
                (vec3){self->position_top[0], self->position_top[1], 0.0f});
  glm_scale(self->model_top,
            (vec3){self->size_top[0], self->size_top[1], 1.0f});
}

#include "pipe.h"

#include <cglm/affine.h>

pipe_t* pipe_create() {
  pipe_t* self = (pipe_t*)malloc(sizeof(pipe_t));
  glm_vec2((float[2]){75, 200}, self->size);
  glm_vec2((float[2]){200, 0}, self->position);
  return self;
}

void pipe_update(pipe_t* self, float dt) {
  glm_mat4_identity(self->model);
  glm_translate(self->model,
                (vec3){self->position[0], self->position[1], 0.0f});
  glm_scale(self->model, (vec3){self->size[0], self->size[1], 1.0f});
}

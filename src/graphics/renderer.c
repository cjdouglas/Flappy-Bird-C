#include "renderer.h"

#include <cglm/cam.h>
#include <stdio.h>
#include <string.h>

#include "../entity/bird.h"

void renderer_init(renderer_t* self, bird_t* bird) {
  self->shader =
      shader_create("res/basic_vertex.glsl", "res/basic_fragment.glsl");
  self->bird = bird;
}

void renderer_init_cam(renderer_t* self, float left, float right, float bottom,
                       float top, float near, float far) {
  glm_ortho(left, right, bottom, top, near, far, self->projection);
}

void renderer_draw(renderer_t* self) {
  shader_bind(self->shader);
  shader_uniform_mat4(self->shader, "model", (float*)self->bird->model);
  shader_uniform_mat4(self->shader, "projection", (float*)self->projection);
  bird_draw(self->bird);
  vao_clear();
  vbo_clear(GL_ARRAY_BUFFER);
}

void renderer_destroy(renderer_t* self) {}

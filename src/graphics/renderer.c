#include "renderer.h"

#include <cglm/cam.h>
#include <stdio.h>
#include <string.h>

#include "../entity/bird.h"

void renderer_init(renderer_t* self, bird_t* bird) {
  self->shader =
      shader_create("res/basic_vertex.glsl", "res/basic_fragment.glsl");
  self->bird = bird;
  float vertices[8] = {0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f};

  self->vao = vao_create();
  self->vbo = vbo_create(GL_ARRAY_BUFFER);
  vao_bind(self->vao);
  vbo_buffer(self->vbo, vertices, 8 * sizeof(float));
  vao_attr(0, 2, GL_FLOAT, 2 * sizeof(float), 0);
  vbo_clear(self->vbo.type);
  vao_clear();
}

void renderer_init_cam(renderer_t* self, float left, float right, float bottom,
                       float top, float near, float far) {
  glm_ortho(left, right, bottom, top, near, far, self->projection);
}

void renderer_draw(renderer_t* self) {
  shader_bind(self->shader);
  shader_uniform_mat4(self->shader, "model", (float*)self->bird->model);
  shader_uniform_mat4(self->shader, "projection", (float*)self->projection);
  vbo_bind(self->vbo);
  vao_bind(self->vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  vao_clear();
  vbo_clear(self->vbo.type);
}

void renderer_destroy(renderer_t* self) {}

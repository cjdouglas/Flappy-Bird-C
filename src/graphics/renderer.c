#include "renderer.h"

#include <cglm/cam.h>
#include <stdio.h>
#include <string.h>

#include "../entity/bird.h"

void renderer_init(renderer_t* self, bird_t* bird, pipes_t* pipe) {
  self->shader =
      shader_create("res/basic_vertex.glsl", "res/basic_fragment.glsl");
  self->bird = bird;
  self->pipe = pipe;
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
  // Init renderer
  shader_bind(self->shader);
  shader_uniform_mat4(self->shader, "projection", (float*)self->projection);

  vbo_bind(self->vbo);
  vao_bind(self->vao);

  // Draw bird
  shader_uniform_vec3(self->shader, "color", (vec3){1.0f, 1.0f, 1.0f});
  shader_uniform_mat4(self->shader, "model", (float*)self->bird->model);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  shader_uniform_vec3(self->shader, "color", (vec3){0.0f, 0.6f, 0.2f});
  shader_uniform_mat4(self->shader, "model", (float*)self->pipe->model_bottom);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  shader_uniform_mat4(self->shader, "model", (float*)self->pipe->model_top);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  vao_clear();
  vbo_clear(self->vbo.type);
}

void renderer_destroy(renderer_t* self) {}

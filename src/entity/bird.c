#include "bird.h"

#include <cglm/affine.h>
#include <stdlib.h>

#define X_START 60
#define Y_START 300
#define WIDTH 30
#define HEIGHT 30
#define GRAVITY 30

bird_t* bird_create() {
  bird_t* self = (bird_t*)malloc(sizeof(bird_t));
  glm_vec2((float[2]){X_START, Y_START - (WIDTH / 2.0f)}, self->position);
  glm_vec2((float[2]){WIDTH, HEIGHT}, self->size);
  self->velocity = 0.0f;
  self->acceleration = GRAVITY;
  glm_mat4_identity(self->model);

  self->vao = vao_create();
  self->vbo = vbo_create(GL_ARRAY_BUFFER);

  size_t n_vertices = 8;
  float vertices[8] = {
      self->position[0],         self->position[1],            // Top left
      self->position[0],         self->position[1] + HEIGHT,   // Bottom left
      self->position[0] + WIDTH, self->position[1],            // Top right
      self->position[0] + WIDTH, self->position[1] + HEIGHT};  // Bottom right

  vao_bind(self->vao);
  vbo_buffer(self->vbo, vertices, n_vertices * sizeof(float));
  vao_attr(0, 2, GL_FLOAT, 2 * sizeof(float), 0);
  vbo_clear(self->vbo.type);
  vao_clear();
  return self;
}

void bird_flap(bird_t* self) {
  self->velocity = -6.9f;
}

void bird_update(bird_t* self, float dt) {
  self->velocity += self->acceleration * dt;
  self->position[1] += self->velocity;
  glm_translate_y(self->model, self->velocity);
}

void bird_draw(bird_t* self) {
  vbo_bind(self->vbo);
  vao_bind(self->vao);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  vao_clear();
  vbo_clear(self->vbo.type);
}

void bird_destroy(bird_t* self) {
  if (self) {
    vao_destroy(self->vao);
    vbo_destroy(self->vbo);
    free(self);
  }
}

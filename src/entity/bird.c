#include "bird.h"

#include <stdlib.h>

#define X_START 100
#define Y_START 300
#define WIDTH 30
#define HEIGHT 30

bird_t* bird_create() {
  bird_t* self = (bird_t*)malloc(sizeof(bird_t));
  self->x = X_START;
  self->y = Y_START - (WIDTH / 2.0f);

  self->vao = vao_create();
  self->vbo = vbo_create(GL_ARRAY_BUFFER);

  size_t n_vertices = 8;
  float vertices[8] = {self->x,         self->y,            // Top left
                       self->x,         self->y + HEIGHT,   // Bottom left
                       self->x + WIDTH, self->y,            // Top right
                       self->x + WIDTH, self->y + HEIGHT};  // Bottom right

  vao_bind(self->vao);
  vbo_buffer(self->vbo, vertices, n_vertices * sizeof(float));
  vao_attr(0, 2, GL_FLOAT, 2 * sizeof(float), 0);
  vbo_clear(self->vbo.type);
  vao_clear();
  return self;
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

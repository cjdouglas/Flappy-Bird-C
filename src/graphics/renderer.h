#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/mat4.h>

#include "shader.h"
#include "vao.h"
#include "vbo.h"
#include "../entity/bird.h"
#include "../entity/pipes.h"

typedef struct renderer {
  shader_t shader;

  bird_t* bird;
  pipes_t** pipes;
  size_t n_pipes;

  mat4 projection;

  vao_t vao;
  vbo_t vbo;
} renderer_t;

void renderer_init(renderer_t* self, bird_t* bird, pipes_t** pipe, size_t n_pipes);
void renderer_init_cam(renderer_t* self, float left, float right, float bottom, float top, float near, float far);
void renderer_draw(renderer_t* self);
void renderer_destroy(renderer_t * self);

#endif // RENDERER_H

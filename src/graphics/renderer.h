#ifndef RENDERER_H
#define RENDERER_H

#include <cglm/mat4.h>

#include "shader.h"
#include "../entity/bird.h"

typedef struct renderer {
  shader_t shader;

  bird_t* bird;

  mat4 projection;
} renderer_t;

void renderer_init(renderer_t* self, bird_t* bird);
void renderer_init_cam(renderer_t* self, float left, float right, float bottom, float top, float near, float far);
void renderer_draw(renderer_t* self);
void renderer_destroy(renderer_t * self);

#endif // RENDERER_H

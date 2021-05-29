#ifndef RENDERER_H
#define RENDERER_H

#include "shader.h"
#include "../entity/bird.h"

typedef struct renderer {
  shader_t shader;

  bird_t* bird;

  float projection[16];
  GLint u_projection_location;
} renderer_t;

void renderer_init(renderer_t* self);
void renderer_draw(renderer_t* self);
void renderer_destroy(renderer_t * self);
void renderer_update_projection(renderer_t* self, float left, float right, float top, float bottom, float near, float far);

#endif // RENDERER_H

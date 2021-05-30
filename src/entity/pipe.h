#ifndef PIPE_H
#define PIPE_H

#include <cglm/vec2.h>
#include <cglm/mat4.h>

typedef struct pipe {
  vec2 size;
  vec2 position;
  float velocity;
  mat4 model;
} pipe_t;

pipe_t* pipe_create();
void pipe_update(pipe_t* self, float dt);

#endif // PIPE_H

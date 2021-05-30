#ifndef PIPE_H
#define PIPE_H

#include <cglm/vec2.h>
#include <cglm/mat4.h>

typedef struct pipes {
  vec2 position_bottom;
  vec2 position_top;

  vec2 size_bottom;
  vec2 size_top;

  float velocity;

  mat4 model_bottom;
  mat4 model_top;
} pipes_t;

pipes_t* pipes_create(const float x0, const float height);
void pipes_update(pipes_t* self, float dt);

#endif // PIPE_H

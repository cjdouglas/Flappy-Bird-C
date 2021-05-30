#ifndef PIPE_H
#define PIPE_H

#include <cglm/vec2.h>
#include <cglm/mat4.h>

#define PIPE_WIDTH 75
#define PIPE_GAP 175
#define PIPE_VELOCITY 150.0f

typedef struct pipes {
  vec2 position_bottom;
  vec2 position_top;

  vec2 size_bottom;
  vec2 size_top;

  mat4 model_bottom;
  mat4 model_top;
} pipes_t;

pipes_t* pipes_create();
void pipes_update(pipes_t* self, float dt);
void pipes_reset(pipes_t* self, const float x0, float height);

#endif // PIPE_H

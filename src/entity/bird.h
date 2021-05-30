#ifndef BIRD_H
#define BIRD_H

#include <cglm/vec2.h>
#include <cglm/mat4.h>

#include "../graphics/vao.h"
#include "../graphics/vbo.h"

typedef struct bird {
  vec2 position;
  vec2 size;
  float velocity;
  float acceleration;

  mat4 model;
} bird_t;

bird_t* bird_create();
void bird_flap(bird_t* self);
void bird_update(bird_t* self, float dt);

#endif // BIRD_H

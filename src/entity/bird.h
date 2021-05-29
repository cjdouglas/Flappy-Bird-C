#ifndef BIRD_H
#define BIRD_H

#include "../graphics/vao.h"
#include "../graphics/vbo.h"

typedef struct bird {
  float x;
  float y;

  vao_t vao;
  vbo_t vbo;
} bird_t;

bird_t* bird_create();
void bird_draw(bird_t* self);
void bird_destroy(bird_t* self);

#endif // BIRD_H

#ifndef GAME_H
#define GAME_H

#include "../entity/bird.h"
#include "../entity/pipes.h"
#include "../graphics/renderer.h"

#define N_PIPES 3

typedef struct game {
  bird_t* bird;
  pipes_t** pipes;
  float cycle_time;
  int cycle_index;
} game_t;

void game_init(game_t* self);
void game_update(game_t* self, float dt);
void game_input(game_t* self, int key);
void game_destroy(game_t* self);

#endif  // GAME_H

#ifndef GAME_H
#define GAME_H

#include "../graphics/renderer.h"
#include "../entity/bird.h"

typedef struct game {
  bird_t* bird;
} game_t;

void game_init(game_t* self);
void game_update(game_t* self, float dt);
void game_input(game_t* self, int key);
void game_destroy(game_t* self);

#endif // GAME_H

#ifndef WINDOW_H
#define WINDOW_H

#include "graphics.h"

typedef void (*window_action_t)();

struct window {
  GLFWwindow* handle;

  int w;
  int h;

  struct {
    window_action_t init, destroy, tick, update, render;
  } actions;
};

typedef struct window window_t;

extern window_t window;

void window_create(window_action_t init, window_action_t destroy, window_action_t tick, window_action_t update, window_action_t render);
void window_mainloop();

#endif // WINDOW_H

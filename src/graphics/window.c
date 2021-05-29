#include "window.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../state.h"

state_t state;
window_t window;

static void _process_input() {
  if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window.handle, true);
  }

  if (glfwGetKey(window.handle, GLFW_KEY_SPACE) == GLFW_PRESS) {
    game_input(&state.game, GLFW_KEY_SPACE);
  }
}

void window_create(window_action_t init, window_action_t destroy,
                   window_action_t render) {
  window.actions.init = init;
  window.actions.destroy = destroy;
  window.actions.render = render;

  if (!glfwInit()) {
    fprintf(stderr, "%s\n", "Error initializing GLFW");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window.w = 400;
  window.h = 600;
  window.handle =
      glfwCreateWindow(window.w, window.h, "Flappy Bird", NULL, NULL);
  if (!window.handle) {
    fprintf(stderr, "%s\n", "Error creating GLFW window");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window.handle);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "%s", "Error initializing GLAD\n");
    glfwTerminate();
    exit(-1);
  }
}

static void _init() {
  window.actions.init();
}

static void _destroy() {
  window.actions.destroy();
  glfwTerminate();
}

static void _render() {
  window.actions.render();
}

static void _update_game(float dt) {
  game_update(&state.game, dt);
}

void window_mainloop() {
  _init();

  float dt = 0.0f;
  float last_frame = 0.0f;

  while (!glfwWindowShouldClose(window.handle)) {
    float current_frame = glfwGetTime();
    dt = current_frame - last_frame;
    last_frame = current_frame;
    _update_game(dt);

    _process_input();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _render();

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }

  _destroy();
  exit(0);
}

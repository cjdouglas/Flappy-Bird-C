#include "window.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

window_t window;

static void _window_resize(GLFWwindow* handle, int width, int height) {
  window.w = width;
  window.h = height;
  GL_CHECK(glViewport(0, 0, window.w, window.h));
}

static void _process_input() {
  if (glfwGetKey(window.handle, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window.handle, true);
  }
}

void window_create(window_action_t init, window_action_t destroy,
                   window_action_t tick, window_action_t update,
                   window_action_t render) {
  window.actions.init = init;
  window.actions.destroy = destroy;
  window.actions.tick = tick;
  window.actions.update = update;
  window.actions.render = render;

  if (!glfwInit()) {
    fprintf(stderr, "%s\n", "Error initializing GLFW");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window.w = 800;
  window.h = 600;
  window.handle =
      glfwCreateWindow(window.w, window.h, "Flappy Bird", NULL, NULL);
  if (!window.handle) {
    fprintf(stderr, "%s\n", "Error creating GLFW window");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window.handle);
  glfwSetFramebufferSizeCallback(window.handle, _window_resize);

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

static void _tick() {
  window.actions.tick();
}

static void _update() {
  window.actions.update();
}

static void _render() {
  window.actions.render();
}

void window_mainloop() {
  _init();

  while (!glfwWindowShouldClose(window.handle)) {
    _process_input();

    // TODO: work with these
    _tick();
    _update();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    _render();

    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }

  _destroy();
  exit(0);
}

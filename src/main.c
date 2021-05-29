#include "graphics/graphics.h"
#include "graphics/renderer.h"
#include "graphics/window.h"

renderer_t renderer;

static void _init() {
  renderer_init(&renderer);
}

static void _destroy() {
  renderer_destroy(&renderer);
}

static void _tick() {}

static void _update() {}

static void _render() {
  renderer_update_projection(&renderer, 0.0f, window.w, 0.0f, window.h, -1.0f,
                             1.0f);
  renderer_draw(&renderer);
}

int main(int argc, char** argv) {
  window_create(_init, _destroy, _tick, _update, _render);
  window_mainloop();

  return 0;
}

#include "graphics/graphics.h"
#include "graphics/window.h"

static void _init() {}

static void _destroy() {}

static void _tick() {}

static void _update() {}

static void _render() {}

int main(int argc, char** argv) {
  window_create(_init, _destroy, _tick, _update, _render);
  window_mainloop();

  return 0;
}

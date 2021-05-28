#include "debug.h"

void GLClearError() {
  while (glGetError() != GL_NO_ERROR) {
  }
}

bool GLLogCall(const char* function, const char* file, int line) {
  GLenum error;
  while ((error = glGetError())) {
    fprintf(stderr, "[OpenGL Error] (%d): %s %s: %d\n", error, function, file,
            line);
    return false;
  }
  return true;
}

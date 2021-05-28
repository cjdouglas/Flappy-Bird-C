#include "vbo.h"

vbo_t vbo_create(GLint type) {
  vbo_t self = {.type = type};
  GL_CHECK(glGenBuffers(1, &self.handle));
  return self;
}

void vbo_destroy(vbo_t self) {
  GL_CHECK(glDeleteBuffers(1, &self.handle));
}

void vbo_bind(vbo_t self) {
  GL_CHECK(glBindBuffer(self.type, self.handle));
}

void vbo_buffer(vbo_t self, void* data, size_t size_bytes) {
  vbo_bind(self);
  GL_CHECK(glBufferData(self.handle, size_bytes, data, GL_STATIC_DRAW));
}

void vbo_clear(GLint type) {
  GL_CHECK(glBindBuffer(type, 0));
}

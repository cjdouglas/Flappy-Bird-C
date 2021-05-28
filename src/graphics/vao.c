#include "vao.h"

vao_t vao_create() {
  vao_t self;
  GL_CHECK(glGenVertexArrays(1, &self.handle));
  return self;
}

void vao_clear() {
  GL_CHECK(glBindVertexArray(0));
}

void vao_destroy(vao_t self) {
  GL_CHECK(glDeleteVertexArrays(1, &self.handle));
}

void vao_bind(vao_t self) {
  GL_CHECK(glBindVertexArray(self.handle));
}

void vao_attr(GLuint index, GLint size, GLenum type, GLsizei stride,
              size_t offset) {
  GL_CHECK(glVertexAttribPointer(index, size, type, GL_FALSE, stride,
                                 (void*)offset));
  GL_CHECK(glEnableVertexAttribArray(index));
}

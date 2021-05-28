#ifndef VAO_H
#define VAO_H

#include "graphics.h"

typedef struct vao {
  GLuint handle;
} vao_t;

vao_t vao_create();
void vao_clear();
void vao_destroy(vao_t self);
void vao_bind(vao_t self);
void vao_attr(GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

#endif // VAO_H

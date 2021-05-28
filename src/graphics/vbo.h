#ifndef VBO_H
#define VBO_H

#include "graphics.h"

typedef struct vbo {
  GLuint handle;
  GLint type;
} vbo_t;

vbo_t vbo_create(GLint type);
void vbo_destroy(vbo_t self);
void vbo_bind(vbo_t self);
void vbo_buffer(vbo_t self, void* data, size_t size_bytes);
void vbo_clear(GLint type);

#endif // VBO_H

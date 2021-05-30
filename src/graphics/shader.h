#ifndef SHADER_H
#define SHADER_H

#include "graphics.h"

struct shader {
  GLuint handle, vertex_handle, fragment_handle;
};

typedef struct shader shader_t;

shader_t shader_create(char* vsh, char* fsh);
void shader_destroy(shader_t self);
void shader_bind(shader_t self);
void shader_uniform_mat4(shader_t self, const char* name, float* mat);
void shader_uniform_vec3(shader_t self, const char* name, float* vec);

#endif  // SHADER_H

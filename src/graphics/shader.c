#include "shader.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _compile(char* path, GLenum type, GLuint* location) {
  FILE* f;
  char* text;
  long len;
  char* shader_type = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";

  f = fopen(path, "rb");
  if (!f) {
    fprintf(stderr, "%s %s\n", "Error opening file at", path);
    exit(1);
  }

  fseek(f, 0, SEEK_END);
  len = ftell(f);
  assert(len > 0);
  fseek(f, 0, SEEK_SET);
  text = calloc(1, len);
  assert(text != NULL);
  fread(text, 1, len, f);
  assert(strlen(text) > 0);
  fclose(f);

  GL_CHECK(GLuint handle = glCreateShader(type));
  GL_CHECK(glShaderSource(handle, 1, (const GLchar* const*)&text,
                          (const GLint*)&len));
  GL_CHECK(glCompileShader(handle));

  GLint compiled;
  GL_CHECK(glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled));
  if (compiled == GL_FALSE) {
    fprintf(stderr, "Error compiling %s shader\n", shader_type);
    free(text);
    exit(1);
  }

  free(text);
  *location = handle;
}

shader_t shader_create(char* vsh, char* fsh) {
  shader_t self;
  _compile(vsh, GL_VERTEX_SHADER, &self.vertex_handle);
  _compile(fsh, GL_FRAGMENT_SHADER, &self.fragment_handle);

  GL_CHECK(self.handle = glCreateProgram());
  GL_CHECK(glAttachShader(self.handle, self.vertex_handle));
  GL_CHECK(glAttachShader(self.handle, self.fragment_handle));
  glLinkProgram(self.handle);

  GLint linked;
  GL_CHECK(glGetProgramiv(self.handle, GL_LINK_STATUS, &linked));
  if (linked == GL_FALSE) {
    GLint length;
    GL_CHECK(glGetShaderiv(self.handle, GL_INFO_LOG_LENGTH, &length));
    char* message = (char*)malloc(length * sizeof(char));
    GL_CHECK(glGetShaderInfoLog(self.handle, length, &length, message));
    fprintf(stderr, "Error linking shader: %s\n", message);
    free(message);
    exit(1);
  }

  return self;
}

void shader_destroy(shader_t self) {
  GL_CHECK(glDeleteProgram(self.handle));
  GL_CHECK(glDeleteShader(self.vertex_handle));
  GL_CHECK(glDeleteShader(self.fragment_handle));
}

void shader_bind(shader_t self) {
  GL_CHECK(glUseProgram(self.handle));
}

void shader_uniform_mat4(shader_t self, const char* name, float* mat) {
  GL_CHECK(glUniformMatrix4fv(glGetUniformLocation(self.handle, name), 1,
                              GL_FALSE, mat));
}

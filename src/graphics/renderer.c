#include "renderer.h"

#include <stdio.h>
#include <string.h>

#include "../entity/bird.h"

static void _create_orthographic(float left, float right, float top,
                                 float bottom, float near, float far,
                                 float* out);

void renderer_init(renderer_t* self) {
  self->shader =
      shader_create("res/basic_vertex.glsl", "res/basic_fragment.glsl");
  self->bird = bird_create();
  GL_CHECK(self->u_projection_location =
               glGetUniformLocation(self->shader.handle, "projection"));
}

void renderer_draw(renderer_t* self) {
  shader_bind(self->shader);
  shader_uniform_mat4(self->shader, "projection", self->projection);
  bird_draw(self->bird);
  vao_clear();
  vbo_clear(GL_ARRAY_BUFFER);
}

void renderer_destroy(renderer_t* self) {
  bird_destroy(self->bird);
}

void renderer_update_projection(renderer_t* self, float left, float right,
                                float top, float bottom, float near,
                                float far) {
  _create_orthographic(left, right, top, bottom, near, far, self->projection);
}

static void _create_orthographic(float left, float right, float top,
                                 float bottom, float near, float far,
                                 float* out) {
  memset(out, 0, 16 * sizeof(float));
  out[0] = 2.0f / (right - left);
  out[5] = 2.0f / (top - bottom);
  out[10] = -2.0f / (far - near);
  out[12] = -(right + left) / (right - left);
  out[13] = -(top + bottom) / (top - bottom);
  out[14] = -(far + near) / (far - near);
  out[15] = 1.0f;
}

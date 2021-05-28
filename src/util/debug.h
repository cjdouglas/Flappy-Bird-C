#ifndef DEBUG_H
#define DEBUG_H

#include <glad/glad.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

#define ASSERT(x)                                                              \
  if (!(x)) raise(SIGKILL)

#define GL_CHECK(stmt)                                                         \
  GLClearError();                                                              \
  stmt;                                                                        \
  ASSERT(GLLogCall(#stmt, __FILE__, __LINE__))

#endif // DEBUG_H

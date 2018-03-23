#include "util.h"

GLenum checkGLError(const char *funcName) {
  GLenum error = glGetError();
  switch(error) {
  case GL_INVALID_ENUM: printf("%s: GL_INVALID_ENUM\n", funcName); break;
  case GL_INVALID_VALUE: printf("%s: GL_INVALID_VALUE\n", funcName); break;
  case GL_INVALID_OPERATION: printf("%s: GL_INVALID_OPERATION\n", funcName); break;
  case GL_INVALID_FRAMEBUFFER_OPERATION: printf("%s: GL_INVALID_FRAMEBUFFER_OPERATION\n", funcName); break;
  case GL_OUT_OF_MEMORY: printf("%s: GL_OUT_OF_MEMORY\n", funcName); break;
  case GL_STACK_UNDERFLOW: printf("%s: GL_STACK_UNDERFLOW\n", funcName); break;
  case GL_STACK_OVERFLOW: printf("%s: GL_STACK_OVERFLOW\n", funcName); break;
  }
  return error;
}

#include "shader.h"

const char *readShaderSource(const char *path) {
  char *source = (char *) malloc(sizeof(char) * 1001);
  memset(source, '\0', 1001);
  FILE *fp = fopen(path, "rb");
  fread(source, 1000, 1, fp);
  fclose(fp);
  return source;
}

GLuint compileShader(const char *path, GLint type) {
  GLuint shader = glCreateShader(type);
  const char *source = readShaderSource(path);
  GLint length = -1;

  glShaderSource(shader, 1, &source, &length);
  free((char *) source);

  glCompileShader(shader);
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    GLsizei bufsize;
    printf("ERROR: Cannot compile shader: %s\n", path);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufsize);
    if (bufsize > 1) {
      char log[bufsize + 1];
      GLint length;
      glGetShaderInfoLog(shader, bufsize, &length, log);
      log[bufsize] = '\0';
      printf("%s\n", log);
    }

    glDeleteShader(shader);
  }
  return shader;
}

FirkinShader *createShader(void) {
  GLuint program = glCreateProgram();
  GLuint vshader = compileShader("./resources/vertex.glsl", GL_VERTEX_SHADER);
  GLuint fshader = compileShader("./resources/fragment.glsl", GL_FRAGMENT_SHADER);
  glAttachShader(program, vshader);
  glAttachShader(program, fshader);
  glBindAttribLocation(program, FIRKIN_ATTRIB_POSITION_INDEX, "position");
  glBindAttribLocation(program, FIRKIN_ATTRIB_TEXCOORD_INDEX, "texCoord");

  glLinkProgram(program);
  GLint status;
  glGetProgramiv(program, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    GLsizei bufsize;
    printf("ERROR: Cannot link program\n");
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufsize);
    if (bufsize > 1) {
      char log[bufsize + 1];
      GLint length;
      glGetProgramInfoLog(program, bufsize, &length, log);
      log[bufsize] = '\0';
      printf("%s\n", log);
    }
    glDeleteProgram(program);
    return NULL;
  }

  FirkinShader *sdr = (FirkinShader *) malloc(sizeof(FirkinShader));
  sdr->program = program;
  return sdr;
}

void useShader(FirkinShader *sdr) {
  glUseProgram(sdr->program);
}

void enableShaderAttributes(FirkinShader *sdr) {
  glUseProgram(sdr->program);
  glEnableVertexAttribArray(FIRKIN_ATTRIB_POSITION_INDEX);
  glUseProgram(0);
}

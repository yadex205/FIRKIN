#ifndef QUAD_H
#define QUAD_H

#include <stdlib.h>
#include <GL/glew.h>
#include "shader.h"
#include "util.h"

typedef struct _s_FirkinQuad {
  GLuint vao;
  GLuint *vbos;
} FirkinQuad;

FirkinQuad *createQuad(void);
void terminateQuad(FirkinQuad *quad);
void setQuadAttribPointer(FirkinQuad *quad);
void drawQuad(FirkinQuad *quad);


#endif /* QUAD_H */

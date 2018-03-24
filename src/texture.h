#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdlib.h>
#include <GL/glew.h>
#include "util.h"
#include "shader.h"

typedef struct _s_FirkinTexture {
  GLuint texId;
} FirkinTexture;

FirkinTexture *createTetxture(void);
void terminateTexture(FirkinTexture *tex);
void setTexturePixels(FirkinTexture *tex, GLuint width, GLuint height, GLenum fmt, GLubyte *data);
void useTexture(FirkinTexture *tex, FirkinShader *sdr);

#endif /* TEXTURE_H */

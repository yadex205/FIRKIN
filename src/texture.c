#include "texture.h"

FirkinTexture *createTetxture(void) {
  GLuint texId;

  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, 0);

  FirkinTexture *tex = (FirkinTexture *) malloc(sizeof(FirkinTexture));
  tex->texId = texId;
  return tex;
}

void setTexturePixels(FirkinTexture *tex, GLuint width, GLuint height, GLenum fmt, GLubyte *data) {
  glBindTexture(GL_TEXTURE_2D, tex->texId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
  tex->width = width;
  tex->height = height;
  glBindTexture(GL_TEXTURE_2D, 0);
};

void terminateTexture(FirkinTexture *tex) {
  glDeleteTextures(1, &(tex->texId));
  free(tex);
}

void useTexture(FirkinTexture *tex, FirkinShader *sdr) {
  glBindTexture(GL_TEXTURE_2D, tex->texId);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(sdr->uniformLocations[FIRKIN_UNIFORM_TEXSAMPLER_INDEX], 0);
}

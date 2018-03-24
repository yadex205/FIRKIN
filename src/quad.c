#include "quad.h"

FirkinQuad *createQuad(void) {
  GLuint vao;
  GLuint vbos[2];
  float positions[12] = { -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f,
                          -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f };
  float texCoords[12] = { 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                          0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(2, vbos);
  glBindBuffer(GL_ARRAY_BUFFER, vbos[FIRKIN_ATTRIB_POSITION_INDEX]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, positions, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, vbos[FIRKIN_ATTRIB_TEXCOORD_INDEX]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, texCoords, GL_STATIC_DRAW);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  FirkinQuad *quad = (FirkinQuad *) malloc(sizeof(FirkinQuad));
  quad->vao = vao;
  quad->vbos = (GLuint *) malloc(sizeof(GLuint) * 1);
  for(int i = 0; i < 2; i++) {
    quad->vbos[i] = vbos[i];
  }
  return quad;
}

void terminateQuad(FirkinQuad *quad) {
  glDeleteBuffers(1, quad->vbos);
  glDeleteVertexArrays(1, &(quad->vao));
  free(quad);
}

void setQuadAttribPointer(FirkinQuad *quad) {
  glBindVertexArray(quad->vao);
  glBindBuffer(GL_ARRAY_BUFFER, quad->vbos[FIRKIN_ATTRIB_POSITION_INDEX]);
  glVertexAttribPointer(FIRKIN_ATTRIB_POSITION_INDEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(FIRKIN_ATTRIB_POSITION_INDEX);
  glBindBuffer(GL_ARRAY_BUFFER, quad->vbos[FIRKIN_ATTRIB_TEXCOORD_INDEX]);
  glVertexAttribPointer(FIRKIN_ATTRIB_TEXCOORD_INDEX, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(FIRKIN_ATTRIB_TEXCOORD_INDEX);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void drawQuad(FirkinQuad *quad) {
  glBindVertexArray(quad->vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

#ifndef SHADER_H
#define SHADER_H

#define FIRKIN_ATTRIB_POSITION_INDEX 0
#define FIRKIN_ATTRIB_TEXCOORD_INDEX 1
#define FIRKIN_UNIFORM_TEXSAMPLER_INDEX 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "util.h"

typedef struct _s_FirkinShader {
  GLuint program;
  GLuint *uniformLocations;
} FirkinShader;

FirkinShader *createShader(void);
void useShader(FirkinShader *sdr);
void enableShaderAttributes(FirkinShader *sdr);

#endif /* SHADER_H */

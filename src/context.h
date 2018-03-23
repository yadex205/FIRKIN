#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct _s_FirkinContext {
  GLFWwindow *window;
  int glewInitialized;
} FirkinContext;

FirkinContext *createContext(void);
void useContext(FirkinContext *ctx);
int shouldContextClose(FirkinContext *ctx);
void terminateContext(FirkinContext *ctx);

void finalizeContextLoop(FirkinContext *ctx);

#endif /* CONTEXT_H */

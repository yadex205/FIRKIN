#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct _s_FirkinContext {
  GLFWwindow *window;
  int glewInitialized;
  double renderInterval;
  double lastRenderedAt;
  struct timespec *_sleepTime;
} FirkinContext;

FirkinContext *createContext(void);
void useContext(FirkinContext *ctx);
int shouldContextClose(FirkinContext *ctx);
void terminateContext(FirkinContext *ctx);

GLboolean initContextLoop(FirkinContext *ctx);
void finalizeContextLoop(FirkinContext *ctx);

#endif /* CONTEXT_H */

#include "context.h"

FirkinContext *createContext(void) {
  GLFWwindow *window = glfwCreateWindow(960, 540, "Firkin", NULL, NULL);

  if (!window) {
    printf("ERROR: Cannot create window\n");
    return NULL;
  }

  glfwSetTime(0.0);

  FirkinContext *ctx = (FirkinContext *) malloc(sizeof(FirkinContext));
  ctx->_sleepTime = (struct timespec *) malloc(sizeof(struct timespec));

  ctx->window = window;
  ctx->glewInitialized = -1;
  ctx->renderInterval = 1.0 / 30.0;
  ctx->lastRenderedAt = glfwGetTime();
  ctx->_sleepTime->tv_sec = 0;
  ctx->_sleepTime->tv_nsec = 0;

  return ctx;
}

void useContext(FirkinContext *ctx) {
  glfwMakeContextCurrent(ctx->window);
  glfwSwapInterval(1);

  if (ctx->glewInitialized < 0) {
    if (glewInit() != GLEW_OK) {
      printf("WARN: Cannot initialize GLEW for current context\n");
      ctx->glewInitialized = 0;
    } else {
      ctx->glewInitialized = 1;
    }
  }
}

int shouldContextClose(FirkinContext *ctx) {
  return glfwWindowShouldClose(ctx->window);
}

void terminateContext(FirkinContext *ctx) {
  glfwDestroyWindow(ctx->window);
  free(ctx->_sleepTime);
  free(ctx);
}

GLboolean initContextLoop(FirkinContext *ctx) {
  double currentTime = glfwGetTime();
  double renderSince = ctx->renderInterval - (currentTime - ctx->lastRenderedAt);

  if (renderSince > 0) {
    ctx->_sleepTime->tv_nsec = renderSince * 1e9;
    nanosleep(ctx->_sleepTime, NULL);
    return GL_FALSE;
  } else {
    ctx->lastRenderedAt = currentTime;
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);
    return GL_TRUE;
  }
}

void finalizeContextLoop(FirkinContext *ctx) {
  glfwSwapBuffers(ctx->window);
  glfwPollEvents();
}

void setDropCBForContext(FirkinContext *ctx, GLFWdropfun callback) {
  glfwSetDropCallback(ctx->window, callback);
}

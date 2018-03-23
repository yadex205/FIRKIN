#include "context.h"

FirkinContext *createContext(void) {
  GLFWwindow *window = glfwCreateWindow(960, 540, "Firkin", NULL, NULL);

  if (!window) {
    printf("ERROR: Cannot create window\n");
    return NULL;
  }

  FirkinContext *ctx = (FirkinContext *) malloc(sizeof(FirkinContext));
  ctx->window = window;
  ctx->glewInitialized = -1;

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
  free(ctx);
}

void finalizeContextLoop(FirkinContext *ctx) {
  glfwSwapBuffers(ctx->window);
  glfwPollEvents();
}

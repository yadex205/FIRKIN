#include "app.h"

FirkinApp* createApp(void) {
  FirkinApp *app = (FirkinApp *) malloc(sizeof(FirkinApp));
  app->glfwInitialized = 0;

  if (!glfwInit()) {
    printf("ERROR: Cannot initialize GLFW\n");
    free(app);
    return NULL;
  }

  app->glfwInitialized = 1;
  glewExperimental = GL_TRUE;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);

  return app;
}

void terminateApp(FirkinApp *app) {
  if (app->glfwInitialized) {
    glfwTerminate();
  }

  free(app);
}

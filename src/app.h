#ifndef APP_H
#define APP_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <libavformat/avformat.h>

typedef struct _s_FirkinApp {
  int glfwInitialized;
} FirkinApp;

FirkinApp* createApp(void);
void terminateApp(FirkinApp *app);

#endif /* APP_H */

#import <Foundation/Foundation.h>
#import <GL/glew.h>
#import <GLFW/glfw3.h>
#import "shader.h"

int glfwInitialized = 0;

int initEnvironment(void) {
  if (!glfwInit()) {
    NSLog(@"ERROR: Cannot initialize GLFW");
    return -1;
  }
  glfwInitialized = 1;
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE,        GLFW_OPENGL_CORE_PROFILE);

  return 0;
}

void destroyEnvironment(void) {
  if (glfwInitialized) {
    glfwTerminate();
  }
}

GLenum checkError(const char *funcName) {
  GLenum error = glGetError();
  switch(error) {
  case GL_INVALID_ENUM: NSLog(@"%s: GL_INVALID_ENUM", funcName); break;
  case GL_INVALID_VALUE: NSLog(@"%s: GL_INVALID_VALUE", funcName); break;
  case GL_INVALID_OPERATION: NSLog(@"%s: GL_INVALID_OPERATION", funcName); break;
  case GL_INVALID_FRAMEBUFFER_OPERATION: NSLog(@"%s: GL_INVALID_FRAMEBUFFER_OPERATION", funcName); break;
  case GL_OUT_OF_MEMORY: NSLog(@"%s: GL_OUT_OF_MEMORY", funcName); break;
  case GL_STACK_UNDERFLOW: NSLog(@"%s: GL_STACK_UNDERFLOW", funcName); break;
  case GL_STACK_OVERFLOW: NSLog(@"%s: GL_STACK_OVERFLOW", funcName); break;
  }
  return error;
}

GLuint createQuad(void) {
  GLuint vao, vbo;
  float positions[8] = {-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 1.0f, 1.0f};

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, positions, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

  return vao;
}

int main(void) {
  if (initEnvironment() < 0) {
    destroyEnvironment();
    return -1;
  }

  GLFWwindow *window = glfwCreateWindow(960, 540, "Firkin", NULL, NULL);
  if (!window) {
    NSLog(@"Cannot create window\n");
    destroyEnvironment();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    NSLog(@"Cannot initialize GLEW");
    destroyEnvironment();
    return -1;
  }

  glfwSwapInterval(1);
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

  Shader *shader = [Shader new];
  [shader use];

  GLuint vao = createQuad();

  glEnableVertexAttribArray(0);

  while(glfwWindowShouldClose(window) != GL_TRUE) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  destroyEnvironment();
  return 0;
}

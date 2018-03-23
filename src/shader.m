#import "shader.h"

@interface Shader()
- (GLuint) createShader:(NSString *)path type:(GLint)type;
@end

@implementation Shader
- (id) init {
  [super init];

  self->program = glCreateProgram();

  GLuint vshader = [self createShader:@"./resources/vertex.glsl" type:GL_VERTEX_SHADER];
  GLuint fshader = [self createShader:@"./resources/fragment.glsl" type:GL_FRAGMENT_SHADER];
  GLint status;
  glAttachShader(self->program, vshader);
  glAttachShader(self->program, fshader);
  glBindAttribLocation(self->program, 0, "position");
  glBindFragDataLocation(self->program, 0, "fragment");
  glLinkProgram(self->program);
  glGetProgramiv(self->program, GL_LINK_STATUS, &status);

  if (status == GL_FALSE) {
    GLsizei bufsize;
    NSLog(@"Failed to link program");
    glGetProgramiv(self->program, GL_INFO_LOG_LENGTH, &bufsize);
    if (bufsize > 1) {
      char log[bufsize + 1];
      GLsizei length;
      glGetProgramInfoLog(self->program, bufsize, &length, &(log[0]));
      NSLog(@"%s", log);
    }
    glDeleteProgram(self->program);
  }

  return self;
}

- (void) use {
  glUseProgram(program);
}

- (GLuint) createShader:(NSString *)path type:(GLint)type {
  GLuint shader = glCreateShader(type);
  GLint status;
  NSString *source_str = [NSString stringWithContentsOfFile:path
                                                   encoding:NSUTF8StringEncoding
                                                      error:nil];
  const char *source = [source_str UTF8String];
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

  if (status == GL_FALSE) {
    GLsizei bufsize;
    NSLog(@"Failed to compile shader: %@", path);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufsize);
    if (bufsize > 1) {
      char log[bufsize + 1];
      GLsizei length;
      glGetShaderInfoLog(shader, bufsize, &length, &(log[0]));
      NSLog(@"%s", log);
    }
    glDeleteShader(shader);
  }

  return shader;
}
@end

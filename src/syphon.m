#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL

#import <GL/glew.h>
#import <GLFW/glfw3.h>
#import <GLFW/glfw3native.h>
#import <Syphon/Syphon.h>
#import "syphon.h"

FirkinSyphonServer *createSyphonServer(const char *name, FirkinContext *ctx) {
  NSOpenGLContext *nsglCtx = glfwGetNSGLContext(ctx->window);
  SyphonServer *server = [[SyphonServer alloc] initWithName:[NSString stringWithUTF8String:name]
                                                    context:[nsglCtx CGLContextObj]
                                                    options:nil];

  FirkinSyphonServer *fss = (FirkinSyphonServer *) malloc(sizeof(FirkinSyphonServer));
  fss->server = (void *) server;
  return fss;
}

void publishSyphonTexture(FirkinSyphonServer *fss, FirkinTexture *tex) {
  [(SyphonServer *)fss->server publishFrameTexture:tex->texId
                                     textureTarget:GL_TEXTURE_2D
                                       imageRegion:NSMakeRect(0, 0, 3, 2)
                                 textureDimensions:NSMakeSize(3, 2)
                                           flipped:YES];
}

void terminateSyphonServer(FirkinSyphonServer *fss) {
  [(SyphonServer *)fss->server stop];
  free(fss);
}

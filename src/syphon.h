#ifndef SYPHON_H
#define SYPHON_H

#include "context.h"
#include "texture.h"

typedef struct _s_FirkinSyphonServer {
  void *server;
} FirkinSyphonServer;

FirkinSyphonServer *createSyphonServer(const char *name, FirkinContext *ctx);
void publishSyphonTexture(FirkinSyphonServer *fss, FirkinTexture *tex);
void terminateSyphonServer(FirkinSyphonServer *fss);

#endif /* SYPHON_H */

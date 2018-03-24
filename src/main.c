#include <GL/glew.h>
#include "app.h"
#include "context.h"
#include "shader.h"
#include "quad.h"
#include "texture.h"
#include "video.h"

int main(void) {
  FirkinApp *app = createApp();
  FirkinContext *ctx = createContext();
  useContext(ctx);

  FirkinShader *sdr = createShader();
  FirkinQuad *quad = createQuad();
  FirkinTexture *tex = createTetxture();
  FirkinVideo *video;

  unsigned char pixels[24] = { 255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255,
                               0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255 };
  setTexturePixels(tex, 3, 2, GL_RGBA, pixels);

  useShader(sdr);
  setQuadAttribPointer(quad);

  if ((video = loadVideo("/Users/canon/Downloads/awa.mp4")) != NULL) {
    readVideoFrame(video);
    while(shouldContextClose(ctx) == GL_FALSE) {
      glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      useShader(sdr);
      useTexture(tex, sdr);
      drawQuad(quad);
      finalizeContextLoop(ctx);
    }

    releaseVideo(video);
  }

  terminateTexture(tex);
  terminateQuad(quad);
  terminateContext(ctx);
  terminateApp(app);
  return 0;
}

#include "app.h"
#include "context.h"
#include "shader.h"
#include "quad.h"
#include "texture.h"
#include "player.h"
#include "syphon.h"

FirkinPlayer *player;

static void dropCallback(GLFWwindow *window, int count, const char **paths) {
  if (count < 1) { return; }

  playMedia(player, paths[0]);
}

int main(void) {
  FirkinApp *app = createApp();
  FirkinContext *ctx = createContext();
  useContext(ctx);

  FirkinShader *sdr = createShader();
  FirkinQuad *quad = createQuad();
  FirkinTexture *tex = createTetxture();
  FirkinSyphonServer *fss = createSyphonServer("Firkin", ctx);
  unsigned char pixels[24] = { 255, 0, 0, 255, 0, 255, 0, 255, 0, 0, 255, 255,
                               0, 0, 255, 255, 255, 255, 255, 255, 0, 0, 0, 255 };
  setTexturePixels(tex, 3, 2, GL_RGBA, pixels);

  useShader(sdr);
  setQuadAttribPointer(quad);
  useTexture(tex, sdr);

  player = createPlayer();
  setDropCBForContext(ctx, dropCallback);

  while(shouldContextClose(ctx) == GL_FALSE) {
    if (initContextLoop(ctx) == GL_TRUE) {
      setMediaFrameToTexture(player, tex);

      useShader(sdr);
      useTexture(tex, sdr);
      publishSyphonTexture(fss, tex);
      drawQuad(quad);
      finalizeContextLoop(ctx);
    }
  }

  terminatePlayer(player);
  terminateSyphonServer(fss);
  terminateTexture(tex);
  terminateQuad(quad);
  terminateContext(ctx);
  terminateApp(app);
  return 0;
}

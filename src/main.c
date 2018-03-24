#include <GL/glew.h>
#include "app.h"
#include "context.h"
#include "shader.h"
#include "quad.h"
#include "video.h"

int main(void) {
  FirkinApp *app = createApp();
  FirkinContext *ctx = createContext();
  useContext(ctx);

  FirkinShader *sdr = createShader();
  FirkinQuad *quad = createQuad();
  FirkinVideo *video;

  useShader(sdr);
  setQuadAttribPointer(quad);

  if ((video = loadVideo("/Users/canon/Downloads/awa.mp4")) != NULL) {
    while(shouldContextClose(ctx) == GL_FALSE) {
      glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);
      useShader(sdr);
      readVideoFrame(video);
      drawQuad(quad);
      finalizeContextLoop(ctx);
    }

    releaseVideo(video);
  }

  terminateQuad(quad);
  terminateContext(ctx);
  terminateApp(app);
  return 0;
}

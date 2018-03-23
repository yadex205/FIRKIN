#include <GL/glew.h>
#include "app.h"
#include "context.h"
#include "shader.h"
#include "quad.h"

int main(void) {
  FirkinApp *app = createApp();
  FirkinContext *ctx = createContext();
  useContext(ctx);

  FirkinShader *sdr = createShader();
  FirkinQuad *quad = createQuad();

  useShader(sdr);
  setQuadAttribPointer(quad);

  while(shouldContextClose(ctx) == GL_FALSE) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    useShader(sdr);
    drawQuad(quad);
    finalizeContextLoop(ctx);
  }

  terminateQuad(quad);
  terminateContext(ctx);
  terminateApp(app);
  return 0;
}

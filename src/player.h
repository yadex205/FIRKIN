#ifndef PLAYER_H
#define PLAYER_H

#include <vlc/vlc.h>
#include "shader.h"
#include "texture.h"

typedef struct _s_FirkinPlayer {
  libvlc_instance_t *libvlc;
  libvlc_media_player_t *mplayer;
  unsigned char *pixels;
} FirkinPlayer;

FirkinPlayer *createPlayer(void);
GLboolean playMedia(FirkinPlayer *player, const char *path);
void stopMedia(FirkinPlayer *player);
void setMediaFrameToTexture(FirkinPlayer *player, FirkinTexture *tex);
void terminatePlayer(FirkinPlayer *player);

#endif /* PLAYER_H */

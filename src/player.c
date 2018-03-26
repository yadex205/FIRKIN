#include "player.h"

static void *lock(void *opaque, void **planes) {
  *planes = opaque;
  return NULL;
}

FirkinPlayer *createPlayer(void) {
  const char *vlcArgv[] = { "--no-xlib", "--no-audio" };

  FirkinPlayer *player = (FirkinPlayer *) malloc(sizeof(FirkinPlayer));
  player->libvlc = libvlc_new(2, vlcArgv);
  player->mplayer = NULL;
  player->pixels = (unsigned char *) malloc(sizeof(unsigned char) * 1280 * 720 * 4);
  return player;
}

GLboolean playMedia(FirkinPlayer *player, const char *path) {
  stopMedia(player);

  libvlc_media_t *media = libvlc_media_new_path(player->libvlc, path);
  player->mplayer = libvlc_media_player_new_from_media(media);
  libvlc_media_release(media);
  libvlc_video_set_callbacks(player->mplayer, lock, NULL, NULL, (void *) player->pixels);
  libvlc_video_set_format(player->mplayer, "RV24", 1280, 720, 1280*3);
  libvlc_media_player_play(player->mplayer);
  return GL_TRUE;
}

void stopMedia(FirkinPlayer *player) {
  if (player->mplayer) {
    libvlc_media_player_stop(player->mplayer);
    libvlc_media_player_release(player->mplayer);
  }
  player->mplayer = NULL;
}

void setMediaFrameToTexture(FirkinPlayer *player, FirkinTexture *tex) {
  setTexturePixels(tex, 1280, 720, GL_RGB, player->pixels);
}

void terminatePlayer(FirkinPlayer *player) {
  stopMedia(player);
  libvlc_release(player->libvlc);
}

#ifndef VIDEO_H
#define VIDEO_H

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>

typedef struct _s_FirkinVideo {
  AVFormatContext *fmtCtx;
  AVCodecContext *vCodecCtx;
  AVFrame *rawFrame;
  AVPacket *packet;
  int vStreamIndex;
} FirkinVideo;

FirkinVideo *loadVideo(const char *path);
void releaseVideo(FirkinVideo *video);
void readVideoFrame(FirkinVideo *video);

#endif /* VIDEO_H */

#include "video.h"

FirkinVideo *loadVideo(const char *path) {
  AVFormatContext *fmtCtx = NULL;
  AVCodecContext *vCodecCtx = NULL;
  AVCodec *vDecoder = NULL;
  AVStream *vStream = NULL;
  int vStreamIndex = -1;
  AVDictionary *opts = NULL;
  av_dict_set(&opts, "refcounted_frames", "0", 0);

  if (avformat_open_input(&fmtCtx, path, NULL, NULL) != 0) {
    printf("ERROR: Cannot open video: %s\n", path);
    return NULL;
  }

  if (avformat_find_stream_info(fmtCtx, NULL) != 0 ||
      (vStreamIndex = av_find_best_stream(fmtCtx, AVMEDIA_TYPE_VIDEO, -1, -1, NULL, 0)) < 0) {
    printf("ERROR: Broken video file: %s\n", path);
    avformat_close_input(&fmtCtx);
    return NULL;
  }
  vStream = fmtCtx->streams[vStreamIndex];

  if (!(vDecoder = avcodec_find_decoder(vStream->codecpar->codec_id))) {
    printf("ERROR: Not supported codec included: %s\n", path);
    avformat_close_input(&fmtCtx);
    return NULL;
  }

  if (!(vCodecCtx = avcodec_alloc_context3(vDecoder)) ||
      (avcodec_parameters_to_context(vCodecCtx, vStream->codecpar)) < 0 ||
      avcodec_open2(vCodecCtx, vDecoder, &opts) < 0) {
    printf("ERROR: Cannot initialize decoder: %s\n", path);
  }

  FirkinVideo *video = (FirkinVideo *) malloc(sizeof(FirkinVideo));
  video->fmtCtx = fmtCtx;
  video->vCodecCtx = vCodecCtx;
  video->vStreamIndex = vStreamIndex;
  video->rawFrame = av_frame_alloc();
  video->packet = (AVPacket *) malloc(sizeof(AVPacket));

  return video;
}

void releaseVideo(FirkinVideo *video) {
  free(video->packet);
  av_free(video->rawFrame);
  avcodec_close(video->vCodecCtx);
  avformat_close_input(&(video->fmtCtx));
  free(video);
}

void readVideoFrame(FirkinVideo *video) {
  if (av_read_frame(video->fmtCtx, video->packet) >= 0 &&
      video->packet->stream_index == video->vStreamIndex &&
      avcodec_send_packet(video->vCodecCtx, video->packet) >= 0) {
    while(avcodec_receive_frame(video->vCodecCtx, video->rawFrame) >= 0) {
    }
  }
}

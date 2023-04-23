#include "VideoFrameObserver.h"

VideoFrameObserver::VideoFrameObserver(agora::rtc::IRtcEngine *rtc_engine)
    : rtc_engine_(rtc_engine) {}

VideoFrameObserver::~VideoFrameObserver() { rtc_engine_ = nullptr; }

bool VideoFrameObserver::EnablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerVideoFrameObserver(this);
    return true;
  }
  return false;
}

bool VideoFrameObserver::DisablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerVideoFrameObserver(nullptr);
    return true;
  }
  return false;
}

bool VideoFrameObserver::onCaptureVideoFrame(
    agora::rtc::VIDEO_SOURCE_TYPE sourceType,
    agora::media::base::VideoFrame &videoFrame) {
  // set the video frame to gray
  int length = videoFrame.uStride * videoFrame.height * 0.5;
  memset(videoFrame.uBuffer, 128, length);
  memset(videoFrame.vBuffer, 128, length);
  return true;
}

bool VideoFrameObserver::onPreEncodeVideoFrame(
    agora::rtc::VIDEO_SOURCE_TYPE sourceType,
    agora::media::base::VideoFrame &videoFrame) {
  return true;
}

bool VideoFrameObserver::onMediaPlayerVideoFrame(
    agora::media::base::VideoFrame &videoFrame, int mediaPlayerId) {
  return true;
}

bool VideoFrameObserver::onRenderVideoFrame(
    const char *channelId, agora::rtc::uid_t remoteUid,
    agora::media::base::VideoFrame &videoFrame) {
  return true;
}

bool VideoFrameObserver::onTranscodedVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  return true;
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE
VideoFrameObserver::getVideoFrameProcessMode() {
  return agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE::
      PROCESS_MODE_READ_WRITE;
}

agora::media::base::VIDEO_PIXEL_FORMAT
VideoFrameObserver::getVideoFormatPreference() {
  return agora::media::base::VIDEO_PIXEL_I420;
}

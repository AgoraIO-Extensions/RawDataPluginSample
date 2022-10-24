#ifndef __IRIS_PLUGIN_CPP_API_H__
#define __IRIS_PLUGIN_CPP_API_H__
#include "iris_plugin_platform.h"
#include <IAgoraMediaEngine.h>
#include <IAgoraRtcEngine.h>

class IRIS_PLUGIN_CPP_API VideoObserverPlugin
    : public agora::media::IVideoFrameObserver {
 public:
  VideoObserverPlugin(agora::rtc::IRtcEngine *rtc_engine);
  ~VideoObserverPlugin();
  bool onCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onSecondaryCameraCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onScreenCaptureVideoFrame(VideoFrame &videoFrame) override;
  bool onSecondaryScreenCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onMediaPlayerVideoFrame(VideoFrame &videoFrame,
                               int mediaPlayerId) override;

  bool onRenderVideoFrame(const char *channelId, agora::rtc::uid_t remoteUid,
                          VideoFrame &videoFrame) override;

  bool onTranscodedVideoFrame(VideoFrame &videoFrame) override;

  virtual bool onPreEncodeVideoFrame(VideoFrame &videoFrame) override;

  virtual bool
  onSecondaryPreEncodeCameraVideoFrame(VideoFrame &videoFrame) override;

  virtual bool onPreEncodeScreenVideoFrame(
      agora::media::base::VideoFrame &videoFrame) override;

  virtual bool
  onSecondaryPreEncodeScreenVideoFrame(VideoFrame &videoFrame) override;

  agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE
  getVideoFrameProcessMode() override;

  agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference() override;
  bool getRotationApplied() override { return true; }

  bool getMirrorApplied() override {
    return IVideoFrameObserver::getMirrorApplied();
  }
  bool enablePlugin();
  bool disablePlugin();
  void setRtcEnginePointer(void *enginePtr);

 private:
  agora::rtc::IRtcEngine *rtc_engine_ = nullptr;
};
#endif

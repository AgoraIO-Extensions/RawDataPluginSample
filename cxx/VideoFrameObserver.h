#pragma once

#include "IAgoraMediaEngine.h"
#include "IAgoraRtcEngine.h"
#include "plugin_base.h"

class IRIS_PLUGIN_CPP_API VideoFrameObserver
    : public agora::media::IVideoFrameObserver {
 public:
  explicit VideoFrameObserver(agora::rtc::IRtcEngine *rtc_engine);

  ~VideoFrameObserver() override;

  bool onCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onSecondaryCameraCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onScreenCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onSecondaryScreenCaptureVideoFrame(VideoFrame &videoFrame) override;

  bool onMediaPlayerVideoFrame(VideoFrame &videoFrame,
                               int mediaPlayerId) override;

  bool onRenderVideoFrame(const char *channelId, agora::rtc::uid_t remoteUid,
                          VideoFrame &videoFrame) override;

  bool onTranscodedVideoFrame(VideoFrame &videoFrame) override;

  bool onPreEncodeVideoFrame(VideoFrame &videoFrame) override;

  bool onSecondaryPreEncodeCameraVideoFrame(VideoFrame &videoFrame) override;

  bool onPreEncodeScreenVideoFrame(
      agora::media::base::VideoFrame &videoFrame) override;

  bool onSecondaryPreEncodeScreenVideoFrame(VideoFrame &videoFrame) override;

  agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE
  getVideoFrameProcessMode() override;

  agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference() override;

  bool getRotationApplied() override { return true; }

  bool getMirrorApplied() override {
    return IVideoFrameObserver::getMirrorApplied();
  }

 public:
  bool EnablePlugin();

  bool DisablePlugin();

 private:
  agora::rtc::IRtcEngine *rtc_engine_ = nullptr;
};

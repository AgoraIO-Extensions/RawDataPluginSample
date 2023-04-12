#pragma once

#include "../include/IAgoraMediaEngine.h"
#include "../include/IAgoraRtcEngine.h"
#include "plugin_base.h"

class PLUGIN_CPP_API VideoFrameObserver
    : public agora::media::IVideoFrameObserver {
 public:
  explicit VideoFrameObserver(agora::rtc::IRtcEngine *rtc_engine);

  ~VideoFrameObserver() override;

  bool onCaptureVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType,
                           VideoFrame &videoFrame) override;

  bool onPreEncodeVideoFrame(agora::rtc::VIDEO_SOURCE_TYPE sourceType,
                             VideoFrame &videoFrame) override;

  bool onMediaPlayerVideoFrame(VideoFrame &videoFrame,
                               int mediaPlayerId) override;

  bool onRenderVideoFrame(const char *channelId, agora::rtc::uid_t remoteUid,
                          VideoFrame &videoFrame) override;

  bool onTranscodedVideoFrame(VideoFrame &videoFrame) override;

  VIDEO_FRAME_PROCESS_MODE getVideoFrameProcessMode() override;

  agora::media::base::VIDEO_PIXEL_FORMAT getVideoFormatPreference() override;

 public:
  bool EnablePlugin();

  bool DisablePlugin();

 private:
  agora::rtc::IRtcEngine *rtc_engine_ = nullptr;
};

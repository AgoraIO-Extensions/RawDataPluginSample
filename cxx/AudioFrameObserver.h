#pragma once

#include "../include/IAgoraMediaEngine.h"
#include "../include/IAgoraRtcEngine.h"
#include "plugin_base.h"

class PLUGIN_CPP_API AudioFrameObserver
    : public agora::media::IAudioFrameObserver,
      public IPlugin {
 public:
  explicit AudioFrameObserver(agora::rtc::IRtcEngine *rtc_engine);

  ~AudioFrameObserver() override;

  bool onPlaybackAudioFrameBeforeMixing(const char *channelId,
                                        agora::rtc::uid_t uid,
                                        AudioFrame &audioFrame) override;

  bool onRecordAudioFrame(const char *channelId,
                          AudioFrame &audioFrame) override;

  bool onPlaybackAudioFrame(const char *channelId,
                            AudioFrame &audioFrame) override;

  bool onMixedAudioFrame(const char *channelId,
                         AudioFrame &audioFrame) override;

  bool onEarMonitoringAudioFrame(AudioFrame &audioFrame) override;

  int getObservedAudioFramePosition() override;

  AudioParams getPlaybackAudioParams() override;

  AudioParams getRecordAudioParams() override;

  AudioParams getMixedAudioParams() override;

  AudioParams getEarMonitoringAudioParams() override;

 public:
  bool EnablePlugin() override;

  bool DisablePlugin() override;

 private:
  agora::rtc::IRtcEngine *rtc_engine_ = nullptr;
};

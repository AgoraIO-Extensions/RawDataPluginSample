#include "AudioFrameObserver.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

AudioFrameObserver::AudioFrameObserver(agora::rtc::IRtcEngine *rtc_engine)
    : rtc_engine_(rtc_engine) {}

AudioFrameObserver::~AudioFrameObserver() { rtc_engine_ = nullptr; }

bool AudioFrameObserver::EnablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerAudioFrameObserver(this);
    return true;
  }
  return false;
}

bool AudioFrameObserver::DisablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerAudioFrameObserver(nullptr);
    return true;
  }
  return false;
}

bool AudioFrameObserver::onPlaybackAudioFrameBeforeMixing(
    const char *channelId, agora::rtc::uid_t uid, AudioFrame &audioFrame) {
  return true;
}

bool AudioFrameObserver::onRecordAudioFrame(const char *channelId,
                                            AudioFrame &audioFrame) {
  auto *buffer = (char *) audioFrame.buffer;
  for (int i = 0; i < audioFrame.bytesPerSample * audioFrame.channels
           * audioFrame.samplesPerChannel;
       i += audioFrame.bytesPerSample) {
    // set the audio frame to noise, if you set the audio frame to silence, you can remove this if statement
    if (i % 2 == 0) { buffer[i] = 0; }
  }
  return true;
}

bool AudioFrameObserver::onPlaybackAudioFrame(const char *channelId,
                                              AudioFrame &audioFrame) {
  return true;
}

bool AudioFrameObserver::onMixedAudioFrame(const char *channelId,
                                           AudioFrame &audioFrame) {
  return true;
}

bool AudioFrameObserver::onEarMonitoringAudioFrame(AudioFrame &audioFrame) {
  return true;
}

int AudioFrameObserver::getObservedAudioFramePosition() {
  return AUDIO_FRAME_POSITION_RECORD;
}

agora::media::IAudioFrameObserver::AudioParams
AudioFrameObserver::getPlaybackAudioParams() {
  return agora::media::IAudioFrameObserver::AudioParams();
}

agora::media::IAudioFrameObserver::AudioParams
AudioFrameObserver::getRecordAudioParams() {
  agora::media::IAudioFrameObserver::AudioParams params;
  params.channels = 2;
  params.samples_per_call = 960;
  params.mode = agora::rtc::RAW_AUDIO_FRAME_OP_MODE_TYPE::
      RAW_AUDIO_FRAME_OP_MODE_READ_WRITE;
  params.sample_rate = 48000;
  return params;
}

agora::media::IAudioFrameObserver::AudioParams
AudioFrameObserver::getMixedAudioParams() {
  return agora::media::IAudioFrameObserver::AudioParams();
}

agora::media::IAudioFrameObserver::AudioParams
AudioFrameObserver::getEarMonitoringAudioParams() {
  return agora::media::IAudioFrameObserver::AudioParams();
}

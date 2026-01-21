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
  static std::random_device rd;
  static std::mt19937 gen(rd());
  
  auto *buffer = static_cast<int16_t *>(audioFrame.buffer);
  int totalSamples = audioFrame.channels * audioFrame.samplesPerChannel;
  
  // Generate white noise: fill audio buffer with random values
  // Noise amplitude can be adjusted via noiseAmplitude (0.0 - 1.0)
  constexpr float noiseAmplitude = 0.3f;
  std::uniform_int_distribution<int16_t> dist(
      static_cast<int16_t>(-32768 * noiseAmplitude),
      static_cast<int16_t>(32767 * noiseAmplitude));
  
  for (int i = 0; i < totalSamples; ++i) {
    buffer[i] = dist(gen);
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

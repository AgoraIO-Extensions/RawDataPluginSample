#include "VideoObserverPlugin.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/spdlog.h"

#if defined(__ANDROID__)

#include "spdlog/sinks/android_sink.h"

#endif

#define IRIS_LOG_PLUGIN_D(...)                                                 \
  SPDLOG_LOGGER_CALL(spdlog::default_logger(), spdlog::level::debug,           \
                     __VA_ARGS__)

void resetPluginLogger() {
  std::string file_path = "./agora-iris-plugin.log";
  std::vector<spdlog::sink_ptr> sinks;
#if defined(__ANDROID__)
  sinks.push_back(std::make_shared<spdlog::sinks::android_sink_mt>());
#else
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_mt>());
#endif

  std::string exception;
  try {
    auto max_size = 1024 * 1024;
    auto max_files = 3;
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        file_path, max_size, max_files));
  } catch (std::exception &e) { exception = e.what(); }

  int pid = 0;
#ifdef _WIN32
  pid = static_cast<int>(::GetCurrentProcessId());
#else
  pid = static_cast<int>(::getpid());
#endif

  auto logger = std::make_shared<spdlog::logger>(std::to_string(pid).c_str(),
                                                 sinks.begin(), sinks.end());
  spdlog::flush_on(spdlog::level::trace);
  spdlog::flush_every(std::chrono::seconds(2));
  spdlog::set_default_logger(logger);
  spdlog::set_level((spdlog::level::level_enum) SPDLOG_LEVEL_TRACE);
}

VideoObserverPlugin::VideoObserverPlugin(agora::rtc::IRtcEngine *rtc_engine)
    : rtc_engine_(rtc_engine) {
  resetPluginLogger();
}

VideoObserverPlugin::~VideoObserverPlugin() { rtc_engine_ = nullptr; }

bool VideoObserverPlugin::EnablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerVideoFrameObserver(this);
    return true;
  }
  return false;
}

bool VideoObserverPlugin::DisablePlugin() {
  if (rtc_engine_) {
    agora::media::IMediaEngine *media_engine = nullptr;
    rtc_engine_->queryInterface(agora::rtc::AGORA_IID_MEDIA_ENGINE,
                                (void **) &media_engine);
    media_engine->registerVideoFrameObserver(nullptr);
    return true;
  }
  return false;
}

bool VideoObserverPlugin::onCaptureVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {

  int length = videoFrame.uStride * videoFrame.height * 0.5;
  memset(videoFrame.uBuffer, 128, length);
  memset(videoFrame.vBuffer, 128, length);

  return true;
}

bool VideoObserverPlugin::onSecondaryCameraCaptureVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onSecondaryCameraCaptureVideoFrame");
  return true;
}

bool VideoObserverPlugin::onScreenCaptureVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onScreenCaptureVideoFrame");
  return true;
}

bool VideoObserverPlugin::onSecondaryScreenCaptureVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onSecondaryScreenCaptureVideoFrame");
  return true;
}

bool VideoObserverPlugin::onMediaPlayerVideoFrame(
    agora::media::base::VideoFrame &videoFrame, int mediaPlayerId) {
  IRIS_LOG_PLUGIN_D("onMediaPlayerVideoFrame");
  return true;
}

bool VideoObserverPlugin::onRenderVideoFrame(const char *channelId,
                                             agora::rtc::uid_t remoteUid,
                                             VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onCaptureVideoFrame");
  return true;
}

bool VideoObserverPlugin::onTranscodedVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onTranscodedVideoFrame");
  return true;
}

bool VideoObserverPlugin::onPreEncodeVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onPreEncodeVideoFrame");
  return true;
}

bool VideoObserverPlugin::onSecondaryPreEncodeCameraVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onSecondaryPreEncodeCameraVideoFrame");
  return true;
}

bool VideoObserverPlugin::onPreEncodeScreenVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onPreEncodeScreenVideoFrame");
  return true;
}

bool VideoObserverPlugin::onSecondaryPreEncodeScreenVideoFrame(
    agora::media::base::VideoFrame &videoFrame) {
  IRIS_LOG_PLUGIN_D("onSecondaryPreEncodeScreenVideoFrame");
  return true;
}

agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE
VideoObserverPlugin::getVideoFrameProcessMode() {
  IRIS_LOG_PLUGIN_D("getVideoFrameProcessMode");
  return agora::media::IVideoFrameObserver::VIDEO_FRAME_PROCESS_MODE::
      PROCESS_MODE_READ_WRITE;
}

agora::media::base::VIDEO_PIXEL_FORMAT
VideoObserverPlugin::getVideoFormatPreference() {
  IRIS_LOG_PLUGIN_D("getVideoFormatPreference");
  agora::media::base::VIDEO_PIXEL_FORMAT format =
      agora::media::base::VIDEO_PIXEL_I420;
  return format;
}

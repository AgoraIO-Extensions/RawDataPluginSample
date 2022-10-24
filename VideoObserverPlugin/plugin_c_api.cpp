#include "Plugin_c_api.h"
#include "VideoObserverPlugin.h"
bool enablePlugin(PluginSamplePtr plugin) {
  if (plugin) {
    return ((VideoObserverPlugin *) plugin)->enablePlugin();
  } else {
    return false;
  }
}

bool disablePlugin(PluginSamplePtr plugin) {
  if (plugin) {
    return ((VideoObserverPlugin *) plugin)->disablePlugin();
  } else {
    return false;
  }
}

PluginSamplePtr createSampePlugin(void *rtcEnginePtr) {
  auto *plugin =
      new VideoObserverPlugin((agora::rtc::IRtcEngine *) rtcEnginePtr);
  return (void *) plugin;
}

void DestroySamplePlugin(PluginSamplePtr plugin) {
  delete (VideoObserverPlugin *) plugin;
}
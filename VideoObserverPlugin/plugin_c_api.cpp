#include "Plugin_c_api.h"
#include "VideoObserverPlugin.h"
bool EnablePlugin(PluginSamplePtr plugin) {
  if (plugin) {
    return ((VideoObserverPlugin *) plugin)->EnablePlugin();
  } else {
    return false;
  }
}

bool DisablePlugin(PluginSamplePtr plugin) {
  if (plugin) {
    return ((VideoObserverPlugin *) plugin)->DisablePlugin();
  } else {
    return false;
  }
}

PluginSamplePtr CreateSampePlugin(void *rtcEnginePtr) {
  auto *plugin =
      new VideoObserverPlugin((agora::rtc::IRtcEngine *) rtcEnginePtr);
  return (void *) plugin;
}

void DestroySamplePlugin(PluginSamplePtr plugin) {
  delete (VideoObserverPlugin *) plugin;
}
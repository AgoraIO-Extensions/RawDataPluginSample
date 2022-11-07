#include "plugin_c_api.h"
#include "VideoFrameObserver.h"

bool EnablePlugin(PluginPtr plugin) {
  if (plugin) {
    return ((VideoFrameObserver *) plugin)->EnablePlugin();
  } else {
    return false;
  }
}

bool DisablePlugin(PluginPtr plugin) {
  if (plugin) {
    return ((VideoFrameObserver *) plugin)->DisablePlugin();
  } else {
    return false;
  }
}

PluginPtr CreateSamplePlugin(void *rtcEnginePtr) {
  auto *plugin =
      new VideoFrameObserver((agora::rtc::IRtcEngine *) rtcEnginePtr);
  return (void *) plugin;
}

void DestroySamplePlugin(PluginPtr plugin) {
  delete (VideoFrameObserver *) plugin;
}

#if defined(__ANDROID__)
#include <jni.h>

extern "C" JNIEXPORT jlong JNICALL
Java_io_agora_rtc_plugin_AgoraRawDataPlugin_createSamplePlugin(
    JNIEnv *env, jobject thiz, jlong native_handle) {
  return (jlong) CreateSamplePlugin((void *) native_handle);
}

extern "C" JNIEXPORT void JNICALL
Java_io_agora_rtc_plugin_AgoraRawDataPlugin_destroySamplePlugin(JNIEnv *env,
                                                                jobject thiz,
                                                                jlong handle) {
  DestroySamplePlugin((PluginPtr) handle);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_io_agora_rtc_plugin_AgoraRawDataPlugin_enablePlugin(JNIEnv *env,
                                                         jobject thiz,
                                                         jlong handle) {
  return EnablePlugin((PluginPtr) handle);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_io_agora_rtc_plugin_AgoraRawDataPlugin_disablePlugin(JNIEnv *env,
                                                          jobject thiz,
                                                          jlong handle) {
  return DisablePlugin((PluginPtr) handle);
}
#endif
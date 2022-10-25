#include "plugin_c_api.h"
#include "VideoObserverPlugin.h"
#if defined(__ANDROID__)
#include <jni.h>
#endif

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

PluginSamplePtr CreateSamplePlugin(void *rtcEnginePtr) {
  auto *plugin =
      new VideoObserverPlugin((agora::rtc::IRtcEngine *) rtcEnginePtr);
  return (void *) plugin;
}

void DestroySamplePlugin(PluginSamplePtr plugin) {
  delete (VideoObserverPlugin *) plugin;
}

#if defined(__ANDROID__)
extern "C" JNIEXPORT jlong JNICALL
Java_io_agora_iris_plugin_IrisVideoPlugin_createSamplePlugin(
    JNIEnv *env, jobject thiz, jlong native_handle) {
  return (jlong) CreateSamplePlugin((void *) native_handle);
}

extern "C" JNIEXPORT void JNICALL
Java_io_agora_iris_plugin_IrisVideoPlugin_destroySamplePlugin(JNIEnv *env,
                                                              jobject thiz,
                                                              jlong handle) {
  DestroySamplePlugin((PluginSamplePtr) handle);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_io_agora_iris_plugin_IrisVideoPlugin_enablePlugin(JNIEnv *env,
                                                       jobject thiz,
                                                       jlong handle) {
  EnablePlugin((PluginSamplePtr) handle);
}

extern "C" JNIEXPORT jboolean JNICALL
Java_io_agora_iris_plugin_IrisVideoPlugin_disablePlugin(JNIEnv *env,
                                                        jobject thiz,
                                                        jlong handle) {
  DisablePlugin((PluginSamplePtr) handle);
}
#endif

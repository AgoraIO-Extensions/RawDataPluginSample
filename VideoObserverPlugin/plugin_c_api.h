#ifndef __IRIS_PLUGIN_C_API_H__
#define __IRIS_PLUGIN_C_API_H__
#include "iris_plugin_platform.h"
typedef void *PluginSamplePtr;
IRIS_PLUGIN_API bool enablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API bool disablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API PluginSamplePtr createSampePlugin(void *rtcEnginePtr);
IRIS_PLUGIN_API void DestroySamplePlugin(PluginSamplePtr plugin);
#endif
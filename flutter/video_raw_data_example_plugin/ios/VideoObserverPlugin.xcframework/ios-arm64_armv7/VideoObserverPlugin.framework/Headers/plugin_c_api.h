#ifndef __IRIS_PLUGIN_C_API_H__
#define __IRIS_PLUGIN_C_API_H__

#include "iris_plugin_platform.h"

typedef void *PluginSamplePtr;
IRIS_PLUGIN_API bool EnablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API bool DisablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API PluginSamplePtr CreateSamplePlugin(void *rtcEnginePtr);
IRIS_PLUGIN_API void DestroySamplePlugin(PluginSamplePtr plugin);

#endif
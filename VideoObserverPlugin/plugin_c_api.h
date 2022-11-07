#ifndef __IRIS_PLUGIN_C_API_H__
#define __IRIS_PLUGIN_C_API_H__

#include "iris_plugin_platform.h"

EXTERN_C_ENTER

typedef void *PluginSamplePtr;
IRIS_PLUGIN_API bool IRIS_PLUGIN_CALL EnablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API bool IRIS_PLUGIN_CALL DisablePlugin(PluginSamplePtr plugin);
IRIS_PLUGIN_API PluginSamplePtr IRIS_PLUGIN_CALL CreateSamplePlugin(void *rtcEnginePtr);
IRIS_PLUGIN_API void IRIS_PLUGIN_CALL DestroySamplePlugin(PluginSamplePtr plugin);

EXTERN_C_LEAVE

#endif
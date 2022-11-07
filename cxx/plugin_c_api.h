#pragma once

#include "plugin_base.h"

typedef void *PluginPtr;

IRIS_PLUGIN_API bool EnablePlugin(PluginPtr plugin);

IRIS_PLUGIN_API bool DisablePlugin(PluginPtr plugin);

IRIS_PLUGIN_API PluginPtr CreateSamplePlugin(void *rtcEnginePtr);

IRIS_PLUGIN_API void DestroySamplePlugin(PluginPtr plugin);

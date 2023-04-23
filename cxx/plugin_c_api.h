#pragma once

#include "plugin_base.h"

typedef void *PluginPtr;

PLUGIN_API bool EnablePlugin(PluginPtr plugin);

PLUGIN_API bool DisablePlugin(PluginPtr plugin);

PLUGIN_API PluginPtr CreateSamplePlugin(void *rtcEnginePtr);

PLUGIN_API void DestroySamplePlugin(PluginPtr plugin);

PLUGIN_API PluginPtr CreateSampleAudioPlugin(void *rtcEnginePtr);

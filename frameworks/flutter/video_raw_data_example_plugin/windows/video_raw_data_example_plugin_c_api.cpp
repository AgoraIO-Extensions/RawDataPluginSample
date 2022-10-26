#include "include/video_raw_data_example_plugin/video_raw_data_example_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "video_raw_data_example_plugin.h"

void VideoRawDataExamplePluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  video_raw_data_example_plugin::VideoRawDataExamplePlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}

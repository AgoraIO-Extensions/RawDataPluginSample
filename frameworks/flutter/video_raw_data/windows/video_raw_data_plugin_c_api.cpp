#include "include/video_raw_data/video_raw_data_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "video_raw_data_plugin.h"

void VideoRawDataPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  video_raw_data::VideoRawDataPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}

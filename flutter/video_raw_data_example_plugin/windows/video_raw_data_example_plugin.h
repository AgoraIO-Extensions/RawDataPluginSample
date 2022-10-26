#ifndef FLUTTER_PLUGIN_VIDEO_RAW_DATA_EXAMPLE_PLUGIN_H_
#define FLUTTER_PLUGIN_VIDEO_RAW_DATA_EXAMPLE_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace video_raw_data_example_plugin {

class VideoRawDataExamplePlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  VideoRawDataExamplePlugin();

  virtual ~VideoRawDataExamplePlugin();

  // Disallow copy and assign.
  VideoRawDataExamplePlugin(const VideoRawDataExamplePlugin&) = delete;
  VideoRawDataExamplePlugin& operator=(const VideoRawDataExamplePlugin&) = delete;

 private:
  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace video_raw_data_example_plugin

#endif  // FLUTTER_PLUGIN_VIDEO_RAW_DATA_EXAMPLE_PLUGIN_H_

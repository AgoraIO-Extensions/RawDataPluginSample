import 'dart:io';

import 'package:video_raw_data/src/native_plugin_api_bindings.dart';
import 'dart:ffi' as ffi;

ffi.DynamicLibrary _loadLib() {
  if (Platform.isWindows) {
    return ffi.DynamicLibrary.open('VideoObserverPlugin.dll');
  }

  if (Platform.isAndroid) {
    return ffi.DynamicLibrary.open("libVideoObserverPlugin.so");
  }

  return ffi.DynamicLibrary.process();
}

class VideoRawDataController {
  VideoRawDataController();

  late final NativePluginApiBinding _binding;
  late final ffi.Pointer<ffi.Void> _pluginPtr;
  bool isInitialized = false;

  /// Initialize to process the video raw data
  /// * [rtcEngineNativeHandle]: the [RtcEngine.getNativeHandle]
  void initialize(int rtcEngineNativeHandle) {
    assert(!isInitialized);
    _binding = NativePluginApiBinding(_loadLib());
    _pluginPtr = _binding.CreateSamplePlugin(
        ffi.Pointer<ffi.Void>.fromAddress(rtcEngineNativeHandle));
    _binding.EnablePlugin(_pluginPtr);
    isInitialized = true;
  }

  /// Stop processing the video raw data
  void dispose() {
    assert(isInitialized);
    _binding.DisablePlugin(_pluginPtr);
    _binding.DestroySamplePlugin(_pluginPtr);
  }
}

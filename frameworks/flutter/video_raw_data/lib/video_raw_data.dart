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

const String _libName = 'AgoraRawDataPlugin';
const String _appLibName = 'video_raw_data';

final ffi.DynamicLibrary _dylib = () {
  if (Platform.isMacOS || Platform.isIOS) {
    return ffi.DynamicLibrary.open('$_appLibName.framework/$_appLibName');
  }
  if (Platform.isAndroid || Platform.isLinux) {
    return ffi.DynamicLibrary.open('lib$_libName.so');
  }
  if (Platform.isWindows) {
    return ffi.DynamicLibrary.open('$_libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}();

class VideoRawDataController {
  VideoRawDataController();

  late final NativePluginApiBinding _binding;
  late final ffi.Pointer<ffi.Void> _pluginPtr;
  bool isInitialized = false;

  /// Initialize to process the video raw data
  /// * [rtcEngineNativeHandle]: the [RtcEngine.getNativeHandle]
  void initialize(int rtcEngineNativeHandle) {
    assert(!isInitialized);
    _binding = NativePluginApiBinding(_dylib);
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

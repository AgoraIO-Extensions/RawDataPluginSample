# Introduction

This repository implements a simple plugin template if you want to make plugins for agora rtc sdk. Then you can refer to
this repository to make your own unique plugin.

# Quick Start

## 1. Environment Configuration

* CMake (3.10+)
* Visual Studio 2019 (Windows)
* Xcode (iOS/macOS)
* Android Studio (Android)
    * Gradle (6.5)
    * NDK (You should set `ANDROID_NDK` into environment variables, Such
      as: `export ANDROID_NDK="$HOME/Library/Android/sdk/ndk/21.1.6352462"`)

## 2. Compile Product

### Windows Platform

Execute in the repository root directory:

```bat
.\scripts\build-windows.bat
```

Copy the generated product to the imported agora rtc sdk (note that there are two folders, x64, Win32)

| SDK type | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/windows/Win32/output/Release/AgoraRawDataPlugin.dll, build/windows/x64/output/Release/AgoraRawDataPlugin.dll | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86, Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86_64 |
| Electron SDK |  build/windows/Win32/output/Release/AgoraRawDataPlugin.dll, build/windows/x64/output/Release/AgoraRawDataPlugin.dll | Any path where the `ffi-napi` could load it |

### Mac Platform

Execute in the repository root directory:

```sh
sh scripts/build-mac.sh
```

Copy the generated product to the already imported agora rtc sdk

| SDK type | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/mac/MAC/output/Release/AgoraRawDataPluginUnity.bundle | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/macOS |
| Electron SDK |  build/mac/MAC/output/Release/AgoraRawDataPlugin.dylib | Any path where the `ffi-napi` could load it |

### iOS Platform

Execute in the repository root directory:

```sh
sh scripts/build-ios.sh
```

Copy the generated product to the already imported agora rtc sdk

| SDK type | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/ios/ALL_ARCHITECTURE/output/Release/AgoraRawDataPlugin.framework | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/iOS |

### Android Platform

Execute in the repository root directory:

In mac platform:

```sh
sh scripts/build-android.sh
```

Copy the generated product to the imported agora rtc sdk (note that there are four folders here, namely x86, x86_64,
armeabi-v7a, arm64-v8a)

| SDK type | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/android/ALL_ARCHITECTURE/output/Release/[x86_64 x86 armeabi-v7a arm64-v8a]/libAgoraRawDataPlugin.so | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/Android/AgoraRtcEngineKit.plugin/libs/[x86_64 x86 armeabi-v7a arm64-v8a] |

## 3. Experience Demo

You can run the built-in plug-in demo of the SDK. Experience the effect after the plug-in is
turned on.

| SDK type | Example Link |
| ---- | ---- |
| Unity SDK | https://github.com/AgoraIO-Extensions/Agora-Unity-Quickstart/blob/release%2F4.1.0/API-Example-Unity/Assets/API-Example/Examples/Advanced/Plugin/PluginSceneSample.cs |
| Electron SDK | https://github.com/AgoraIO-Extensions/Electron-SDK/blob/release%2F4.1.0/example/src/renderer/examples/advanced/ProcessVideoRawData/ProcessVideoRawData.tsx |

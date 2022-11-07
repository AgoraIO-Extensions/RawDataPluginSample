# Introduction
This repository implements a simple plugin template if you want to make plugins for agora rtc sdk. Then you can refer to this repository to make your own unique plugin.  

# Quick Start
## 1. Environment Configuration
* CMake
* Xcode (mac os)
* visual studio 2016 (windows)  

## 2. Compile product
#### （1）Mac Platform
Execute in the repository root directory:
```sh
sh dcg/ci/build-mac.sh
```
Copy the generated product to the already imported agora rtc sdk
|  SDK type   | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/mac/MAC/output/Release/VideoObserverPluginUnity.bundle | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/macOS |
|

### (2) IOS Platform
Execute in the repository root directory:
```sh
sh dcg/ci/build-ios.sh
```
 将生成的产物拷贝至已经导入的agora rtc sdk内  
|  SDK type  | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/ios/ALL_ARCHITECTURE/output/Release/VideoObserverPlugin.framework | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/iOS |
|

### (3) Android Platform
Execute in the repository root directory:
In mac platform:
```sh
sh dcg/ci/build-android.sh
```
In windows platform
```bat
.\dcg\ci\build-android.bat
```
Copy the generated product to the imported agora rtc sdk (note that there are four folders here, namely x86, x86_64, armeabi-v7a, arm64-v8a)
|  SDK type  | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/android/ALL_ARCHITECTURE/output/Release/x86_64(x86,armeabi-v7a,arm64-v8a)/libVideoObserverPlugin.so | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/Android/AgoraRtcEngineKit.plugin/libs/x86_64(x86,armeabi-v7a,arm64-v8a) |

### (4) Windows Platform
Execute in the repository root directory:
```bat
.\dcg\ci\build-windows.bat
```

Copy the generated product to the imported agora rtc sdk (note that there are two folders, x64, Win32)
|  SDK type  | Generate product | Copy to SDK directory |
| ---- | ---- | ---- |
| Unity SDK |  build/windows/Win32/output/Release/VideoObserverPlugin.dll, build/windows/x64/output/Release/VideoObserverPlugin.dll | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86, Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86_64, |

## 3. Experience Demo
After copying is completed. You can run the built-in plug-in demo of the SDK. Experience the effect after the plug-in is turned on
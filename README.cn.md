# 仓库介绍
本仓库实现了一个简单的插件模板，如果你想要为agora rtc sdk制作插件。那么可以参考此仓库来制作属于自己独特的插件。  

# 快速体验

### 1.环境配置
* CMake
* Xcode (mac os)
* visual studio 2016 (windows)  

### 2.编译产物
#### （1）mac os 产物()
在仓库根目录下执行:
```sh
sh dcg/ci/build-mac.sh
```
 
 将生成的产物拷贝至已经导入的agora rtc sdk内  
|  SDK类型   | 生成产物 | 拷贝至SDK目录 |
| ---- | ---- | ---- |
| Unity SDK |  build/mac/MAC/output/Release/VideoObserverPluginUnity.bundle | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/macOS |
|

#### （2）iOS 产物()
在仓库根目录下执行:
```sh
sh dcg/ci/build-ios.sh
```
 
 将生成的产物拷贝至已经导入的agora rtc sdk内  
|  SDK类型  | 生成产物 | 拷贝至SDK目录 |
| ---- | ---- | ---- |
| Unity SDK |  build/ios/ALL_ARCHITECTURE/output/Release/VideoObserverPlugin.framework | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/iOS |
|

#### （3）Android 产物
在仓库根目录下执行:  
mac平台
```sh
sh dcg/ci/build-android.sh
```
windows平台
```bat
.\dcg\ci\build-android.bat
```

 
 将生成的产物拷贝至已经导入的agora rtc sdk内(注意，这里有四个文件夹，分别是x86, x86_64, armeabi-v7a, arm64-v8a) 
|  SDK类型  | 生成产物 | 拷贝至SDK目录 |
| ---- | ---- | ---- |
| Unity SDK |  build/android/ALL_ARCHITECTURE/output/Release/x86_64(x86,armeabi-v7a,arm64-v8a)/libVideoObserverPlugin.so | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/Android/AgoraRtcEngineKit.plugin/libs/x86_64(x86,armeabi-v7a,arm64-v8a) |

#### （4）Windows 产物
windows平台
```bat
.\dcg\ci\build-windows.bat
```
 将生成的产物拷贝至已经导入的agora rtc sdk内(注意，这里有两个文件夹，分别是x64, Win32) 
|  SDK类型  | 生成产物 | 拷贝至SDK目录 |
| ---- | ---- | ---- |
| Unity SDK |  build/windows/Win32/output/Release/VideoObserverPlugin.dll, build/windows/x64/output/Release/VideoObserverPlugin.dll | Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86, Assets/Agora-RTC-Plugin/Agora-Unity-RTC-SDK/Plugins/x86_64, |

# 运行demo
上述生成的产物，拷贝完毕后。即可运行SDK内置的插件demo。体验插件开启后的效果
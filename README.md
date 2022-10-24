# Iris

Agora 跨平台 SDK 基础模块

## 开发环境

* [Git](https://git-scm.com/)

* 推荐安装 [CLion](https://www.jetbrains.com/clion/) 或 [VSCode](https://code.visualstudio.com/)

    * [CMake](https://cmake.org/) 构建项目
    * [ClangFormat](https://releases.llvm.org/10.0.0/tools/clang/docs/ClangFormat.html) 格式化代码
    * [RapidJson](https://github.com/Tencent/rapidjson) 解析 JSON
    * [GTest](https://github.com/google/googletest) 执行 UnitTest

* [NDK r18b](https://developer.android.com/ndk/downloads/older_releases) 并配置环境变量 **$ANDROID_NDK**

## 快速开始 

***Windows 请使用 Git Bash***

#### 1、克隆代码

```shell
git clone ssh://git@git.agoralab.co/aduc/iris.git

cd iris

git submodule update --init
```

#### 2、编译代码

```shell
./rtc/ci/build-[Platform].[sh|bat] [Arch] [Debug/Release]
```

Platform:

* Android
* iOS
* Mac
* Windows

Arch:

* Android
    * arm64-v8a
    * armeabi-v7a
    * x86
    * x86_64
* iOS
    * OS64COMBINED
    * SIMULATOR64
* Mac
    * MAC
    * MAC_ARM64
* Windows
    * Win32
    * x64
  
Output: `build/[Platform]/[Arch]/output/`

#### 3、UnitTest（仅支持桌面端）

上述步骤会生成 `IrisUnitTests` 可执行程序

## 如何使用

* 查看 [include](./rtc/cxx/include) 目录, 入口头文件为 [iris_engine.h](rtc/cxx/include/iris_rtc_engine.h)
* 查看代码示例 [test](rtc/cxx/test) 目录以参考实现，

## 注意事项

* 上层框架使用 ApiType 和 Json 字符串与 Iris 通信，Iris 解析后与 Native RTC SDK 通信
* 句柄使用 `uint64_t` 解析，Iris 会转换成 `void *`，所以上层需要转成 Number 类型
* 所有参数名严格与 Native RTC SDK 对齐，关系到透传的 Json 字符串中的 key

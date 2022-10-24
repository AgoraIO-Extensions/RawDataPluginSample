@echo off
set shell_path=%~dp0
set root_path=%shell_path%..\..
set ANDROID_NDK=%ANDROID_NDK_ROOT%

if "%1" == "build" (
    call:build %2 %3
) else (
    echo "start build arm64-v8a ----------"
    call:build arm64-v8a Release
    echo "start build armeabi-v7a ----------"
    call:build armeabi-v7a Release
    echo "start build x86 ----------"
    call:build x86 Release
    echo "start build x86_64 ----------"
    call:build x86_64 Release
)

exit /b 0

:build
    cd %root_path%
    md .\build\android\%~1
    cd .\build\android\%~1
    cmake ^
        -G "MinGW Makefiles" ^
        -DANDROID_ABI=%~1 ^
        -DANDROID_NDK=%ANDROID_NDK% ^
        -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\build\cmake\android.toolchain.cmake ^
        -DANDROID_TOOLCHAIN=clang ^
        -DANDROID_PLATFORM=android-16 ^
        -DCMAKE_BUILD_TYPE=%~2 ^
        -DIRIS_SDK_TYPE=DCG ^
        %root_path%
    cmake --build . --config %~2
    cd %shell_path%
goto:eof

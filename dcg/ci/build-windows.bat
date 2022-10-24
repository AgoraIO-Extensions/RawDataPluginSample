@echo off
set shell_path=%~dp0
set root_path=%shell_path%..\..

if "%1" == "build" (
    if "%4" == "Audio" (
        set sdkType=Audio
    ) else (
        set sdkType=Video
    )
    call:build %2 %3 %sdkType%
) else (
    if "%1" == "buildALL" (
        if "%3" == "Audio" (
            set sdkType=Audio
        ) else (
            set sdkType=Video
        )
        call:buildALL %2 %sdkType%
    ) else (
        if "%1" == "Audio" (
            set sdkType=Audio
        ) else (
            set sdkType=Video
        )
        call:buildALL Release %sdkType%
    )
)

exit /b 0

:build
    cd %root_path%
    md .\build\windows\%~1
    cd .\build\windows\%~1
    cmake ^
        -G "Visual Studio 16 2019" ^
        -A %~1 ^
        -DCMAKE_BUILD_TYPE=%~2 ^
        -DIRIS_SDK_TYPE=%~3 ^
        %root_path%
    cmake --build . --config %~2
    cd %shell_path%
goto:eof

:buildALL
    set buildType=%~1
    set sdkType=%~2
    echo "start build Wind32 ----------"
    call:build Win32 %buildType% %sdkType%
    echo "start build x64 ----------"
    call:build x64 %buildType% %sdkType%
goto:eof

@echo off
set shell_path=%~dp0
set root_path=%shell_path%..

if "%1" == "build" (
    call:build %2 %3
) else (
    if "%1" == "buildALL" (
        call:buildALL %2
    ) else (
        call:buildALL Release
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
    echo "start build Wind32 ----------"
    call:build Win32 %buildType%
    echo "start build x64 ----------"
    call:build x64 %buildType%
goto:eof

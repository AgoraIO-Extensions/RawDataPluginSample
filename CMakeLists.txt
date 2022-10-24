cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(iris_plugin)
set(LIBRARY_NAME iris-plugin)
set(IRIS_PLUGIN_VERSION_MAJOR 4)
set(IRIS_PLUGIN_VERSION_MINOR 1)
set(IRIS_PLUGIN_VERSION_PATCH 0)
set(IRIS_PLUGIN_VERSION_TWEAK 0)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(BUILD_UNITY_BUNDLE TRUE)
    set(IRIS_PLUGIN_PLATFORM "Mac")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(IRIS_PLUGIN_PLATFORM "Linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(IRIS_PLUGIN_PLATFORM "Windows")
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
    set(IRIS_PLUGIN_PLATFORM "iOS")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
    set(IRIS_PLUGIN_PLATFORM "Android")
endif ()
message(STATUS "IRIS_PLUGIN_PLATFORM ${IRIS_PLUGIN_PLATFORM}")

set(IRIS_PLUGIN_VERSION "${IRIS_PLUGIN_VERSION_MAJOR}.${IRIS_PLUGIN_VERSION_MINOR}.${IRIS_PLUGIN_VERSION_PATCH}")
if (IRIS_PLUGIN_VERSION_TWEAK)
    string(APPEND IRIS_PLUGIN_VERSION ".${IRIS_PLUGIN_VERSION_TWEAK}")
endif ()
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/output/")
set(OUTPUT_DIR_REAL "${OUTPUT_DIR}/${CMAKE_BUILD_TYPE}")
set(LIBRARY_OUTPUT_NAME "VideoObserverPlugin")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Download and extract the SDK binary distribution (executes sdk.download.cmake).
include(sdk.download)

set(SDK_TYPE "Agora_Native_SDK")
set(SDK_SUFFIX "FULL")
set(SDK_DOWNLOAD_DIR "${CMAKE_SOURCE_DIR}/third_party/agora/dcg/libs")

# set download url
include(sdk.url)

DOWNLOAD_SDK_BY_URL("${SDK_DOWNLOAD_URL}" "${SDK_DOWNLOAD_DIR}")
set(SDK_ROOT "${SDK_DOWNLOAD_DIR}/${SDK_TYPE}_for_${IRIS_PLUGIN_PLATFORM}_${SDK_SUFFIX}")

if (APPLE)
    include(framework)
    if (NOT IS_DIRECTORY "${SDK_ROOT}/libs/ALL_ARCHITECTURE")
        if (APPLE AND NOT IOS)
            execute_process(
                    COMMAND sh to-framework-mac.sh "${SDK_ROOT}"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake"
            )
        else ()
            execute_process(
                    COMMAND sh to-framework.sh "${SDK_ROOT}"
                    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/cmake"
            )
        endif ()
    endif ()
    set(LIBS_DIR_ROOT "${SDK_ROOT}/libs")
    if (IS_DIRECTORY "${LIBS_DIR_ROOT}/AgoraRtcKit.xcframework")
        if (APPLE AND NOT IOS)
            set(LIBS_DIR "${LIBS_DIR_ROOT}/AgoraRtcKit.xcframework/macos-arm64_x86_64")
        else ()
            if (PLATFORM MATCHES "^SIMULATOR.*$")
                set(LIBS_DIR "${LIBS_DIR_ROOT}/AgoraRtcKit.xcframework/ios-arm64_x86_64-simulator")
            else ()
                set(LIBS_DIR "${LIBS_DIR_ROOT}/AgoraRtcKit.xcframework/ios-arm64_armv7")
            endif ()
        endif ()
    else ()
        set(LIBS_DIR "${LIBS_DIR_ROOT}")
    endif ()
    set(INCLUDE_DIR "${LIBS_DIR}/AgoraRtcKit.framework/Headers")
elseif (WIN32)
    if (CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(LIBS_DIR_ROOT "${SDK_ROOT}/sdk")
        set(LIBS_DIR "${LIBS_DIR_ROOT}/x86_64")
    else ()
        set(LIBS_DIR_ROOT "${SDK_ROOT}/sdk")
        set(LIBS_DIR "${LIBS_DIR_ROOT}/x86")
    endif ()
    set(INCLUDE_DIR "${LIBS_DIR_ROOT}/high_level_api/include")
    set(IRIS_PLUGIN_VERSION_INFO_RC ${CMAKE_BINARY_DIR}/VersionInfo.rc)
    configure_file("${PROJECT_SOURCE_DIR}/cmake/VersionInfo.rc.in" "${IRIS_PLUGIN_VERSION_INFO_RC}")
elseif (ANDROID)
    set(LIBS_DIR_ROOT "${SDK_ROOT}/rtc/sdk")
    set(LIBS_DIR "${LIBS_DIR_ROOT}/${ANDROID_ABI}")
    set(INCLUDE_DIR "${LIBS_DIR_ROOT}/high_level_api/include")
elseif (UNIX)
    set(LIBS_DIR_ROOT "${SDK_ROOT}/sdk")
    set(LIBS_DIR "${LIBS_DIR_ROOT}")
    set(INCLUDE_DIR "${LIBS_DIR_ROOT}/high_level_api/include")
endif ()
message(STATUS "LIBS_DIR_ROOT " ${LIBS_DIR_ROOT})
message(STATUS "LIBS_DIR " ${LIBS_DIR})
message(STATUS "INCLUDE_DIR " ${INCLUDE_DIR})
link_directories(${LIBS_DIR})

set(SRC_PATH ${PROJECT_SOURCE_DIR}/VideoObserverPlugin)

file(GLOB IRIS_PLUGIN_OBSERVER_PUBLIC_HEADER "${SRC_PATH}/*.h")
file(GLOB IRIS_PLUGIN_OBSERVER_PUBLIC_SOURCE "${SRC_PATH}/*.cpp")

if (NOT APPLE)
    file(MAKE_DIRECTORY "${OUTPUT_DIR}/include")
    execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${IRIS_PLUGIN_OBSERVER_PUBLIC_HEADER} "${OUTPUT_DIR}/include"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            )
endif ()

add_library(${LIBRARY_NAME} SHARED
        ${IRIS_PLUGIN_OBSERVER_PUBLIC_HEADER}
        ${IRIS_PLUGIN_OBSERVER_PUBLIC_SOURCE}
        ${IRIS_PLUGIN_VERSION_INFO_RC}
        )
set_target_properties(${LIBRARY_NAME} PROPERTIES
        VERSION "${IRIS_PLUGIN_VERSION}"
        SOVERSION "${IRIS_PLUGIN_VERSION}"
        PUBLIC_HEADER "${IRIS_PLUGIN_OBSERVER_PUBLIC_HEADER}"
        ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        OUTPUT_NAME "${LIBRARY_OUTPUT_NAME}"
        )

set(IRIS_PLUGIN_INCLUDE_DIRS
        "${INCLUDE_DIR}"
        "${PROJECT_SOURCE_DIR}/third_party/spdlog/include"
        )

target_include_directories(${LIBRARY_NAME} PUBLIC
        "$<BUILD_INTERFACE:${IRIS_PLUGIN_INCLUDE_DIRS}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
        )

if (APPLE)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            FRAMEWORK TRUE
            FRAMEWORK_VERSION A
            MACOSX_FRAMEWORK_IDENTIFIER io.agora.iris.plugin.video
            MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${IRIS_PLUGIN_VERSION}"
            MACOSX_FRAMEWORK_BUNDLE_VERSION "${IRIS_PLUGIN_VERSION}"
            CXX_VISIBILITY_PRESET hidden
            LINK_FLAGS "-Wl -F ${LIBS_DIR} -rpath @loader_path/../../../../Frameworks -rpath @loader_path/../../.."
            )
    LINK_FRAMEWORK(${LIBS_DIR_ROOT} ${LIBRARY_NAME})
elseif (WIN32)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE IRIS_PLUGIN_EXPORT)
elseif (ANDROID)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            )
    find_library(log-lib log)
    target_link_libraries(${LIBRARY_NAME}
            PRIVATE
            ${log-lib}
            )
elseif (UNIX)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR_REAL}"
            LINK_FLAGS "-Wl,-rpath,./"
            )
endif ()

add_subdirectory(${PROJECT_SOURCE_DIR}/third_party/spdlog spdlog)

if (BUILD_UNITY_BUNDLE)
    add_library(${LIBRARY_NAME}-unity MODULE
            ${IRIS_PLUGIN_OBSERVER_PUBLIC_HEADER}
            ${IRIS_PLUGIN_OBSERVER_PUBLIC_SOURCE}
            )
    set_target_properties(${LIBRARY_NAME}-unity PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            OUTPUT_NAME "${LIBRARY_OUTPUT_NAME}Unity"
            )

    target_include_directories(${LIBRARY_NAME}-unity PUBLIC
            "$<BUILD_INTERFACE:${IRIS_PLUGIN_INCLUDE_DIRS}>"
            "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
            )
    set_target_properties(${LIBRARY_NAME}-unity PROPERTIES
            BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER io.agora.iris.plugin.video
            MACOSX_BUNDLE_SHORT_VERSION_STRING "${IRIS_PLUGIN_VERSION}"
            MACOSX_BUNDLE_BUNDLE_VERSION "${IRIS_PLUGIN_VERSION}"
            CXX_VISIBILITY_PRESET hidden
            XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
            LINK_FLAGS "-Wl -F ${LIBS_DIR} -rpath @loader_path/../Frameworks"
            )
    target_link_libraries(${LIBRARY_NAME}-unity
            PRIVATE
            "${FRAMEWORKS}"
            )
    LINK_FRAMEWORK(${LIBS_DIR_ROOT} ${LIBRARY_NAME}-unity)
endif ()

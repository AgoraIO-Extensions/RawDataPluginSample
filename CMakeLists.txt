cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(raw-data-plugin)

# Make it simple to extract by script
set(IRIS_PLUGIN_VERSION "0.1.0")

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG")
    if (MSVC)
        set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd /Zi /arch:SSE2")
        set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT /Zi /arch:SSE2")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MT /Zi /arch:SSE2")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT /Zi /arch:SSE2")
    endif ()
else ()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")
endif ()

if (APPLE AND NOT IOS)
    set(CMAKE_XCODE_ATTRIBUTE_MACOSX_DEPLOYMENT_TARGET "10.10")
    set(CMAKE_XCODE_ATTRIBUTE_DEBUG_INFORMATION_FORMAT "dwarf-with-dsym")
    set(BUILD_UNITY_BUNDLE TRUE)
endif ()

set(LIBRARY_NAME raw-data-plugin)
set(LIBRARY_OUTPUT_NAME "AgoraRawDataPlugin")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/output/")
set(OUTPUT_DIR_REAL "${OUTPUT_DIR}/${CMAKE_BUILD_TYPE}")

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(SRC_DIR ${CMAKE_SOURCE_DIR}/cxx)
file(GLOB PLUGIN_HEADER "${SRC_DIR}/*.h")
file(GLOB PLUGIN_SOURCE "${SRC_DIR}/*.cpp")

add_library(${LIBRARY_NAME} SHARED
        ${PLUGIN_HEADER}
        ${PLUGIN_SOURCE}
        ${PLUGIN_VERSION_INFO_RC}
        )
set_target_properties(${LIBRARY_NAME} PROPERTIES
        VERSION "${PLUGIN_VERSION}"
        SOVERSION "${PLUGIN_VERSION}"
        PUBLIC_HEADER "${PLUGIN_HEADER}"
        ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        OUTPUT_NAME "${LIBRARY_OUTPUT_NAME}"
        )

set(PLUGIN_INCLUDE_DIRS "${INCLUDE_DIR}")

target_include_directories(${LIBRARY_NAME} PUBLIC
        "$<BUILD_INTERFACE:${PLUGIN_INCLUDE_DIRS}>"
        "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
        )

if (APPLE)
    set_target_properties(${LIBRARY_NAME} PROPERTIES
            frameworks TRUE
            FRAMEWORK_VERSION A
            MACOSX_FRAMEWORK_IDENTIFIER io.agora.rtc.plugin
            MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${PLUGIN_VERSION}"
            MACOSX_FRAMEWORK_BUNDLE_VERSION "${PLUGIN_VERSION}"
            CXX_VISIBILITY_PRESET hidden
            COMPILE_OPTIONS "-g"
            )
elseif (WIN32)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE PLUGIN_EXPORT)
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
endif ()

if (BUILD_UNITY_BUNDLE)
    add_library(${LIBRARY_NAME}-unity MODULE
            ${PLUGIN_HEADER}
            ${PLUGIN_SOURCE}
            )
    set_target_properties(${LIBRARY_NAME}-unity PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            PDB_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
            OUTPUT_NAME "${LIBRARY_OUTPUT_NAME}Unity"
            )

    target_include_directories(${LIBRARY_NAME}-unity PUBLIC
            "$<BUILD_INTERFACE:${PLUGIN_INCLUDE_DIRS}>"
            "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
            )
    set_target_properties(${LIBRARY_NAME}-unity PROPERTIES
            BUNDLE TRUE
            MACOSX_BUNDLE_GUI_IDENTIFIER io.agora.rtc.plugin
            MACOSX_BUNDLE_SHORT_VERSION_STRING "${PLUGIN_VERSION}"
            MACOSX_BUNDLE_BUNDLE_VERSION "${PLUGIN_VERSION}"
            CXX_VISIBILITY_PRESET hidden
            XCODE_ATTRIBUTE_ENABLE_BITCODE "NO"
            )
endif ()

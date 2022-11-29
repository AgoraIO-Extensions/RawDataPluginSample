# The Flutter tooling requires that developers have CMake 3.10 or later
# installed. You should not increase this version, as doing so will cause
# the plugin to fail to compile for some customers of the plugin.
cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME raw-data-plugin)
set(LIBRARY_OUTPUT_NAME "AgoraRawDataPlugin")

set(LIBRARY_VERSION "0.1.0")

project(${LIBRARY_NAME} VERSION ${LIBRARY_VERSION})

set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../../../../include")
set(SRC_DIR ${CMAKE_SOURCE_DIR}/../../../../cxx)
file(GLOB PLUGIN_HEADER "${SRC_DIR}/*.h")
file(GLOB PLUGIN_SOURCE "${SRC_DIR}/*.cpp")

add_library(${LIBRARY_NAME} SHARED
  ${PLUGIN_HEADER}
  ${PLUGIN_SOURCE}
)

set_target_properties(${LIBRARY_NAME} PROPERTIES
        OUTPUT_NAME "${LIBRARY_OUTPUT_NAME}"
        )

# set_target_properties(hello PROPERTIES
#   PUBLIC_HEADER hello.h
#   OUTPUT_NAME "hello"
# )

target_compile_definitions(${LIBRARY_NAME} PUBLIC DART_SHARED_LIB)

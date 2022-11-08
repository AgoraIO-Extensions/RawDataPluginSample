#pragma once

#include <stdint.h>
#if defined(__APPLE__)
#include <TargetConditionals.h>
#endif

#ifdef __cplusplus
#define EXTERN_C extern "C"
#define EXTERN_C_ENTER extern "C" {
#define EXTERN_C_LEAVE }
#else
#define EXTERN_C
#define EXTERN_C_ENTER
#define EXTERN_C_LEAVE
#endif

#ifdef __GNUC__
#define AGORA_GCC_VERSION_AT_LEAST(x, y)                                       \
  (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#define AGORA_GCC_VERSION_AT_LEAST(x, y) 0
#endif

#if defined(_WIN32)
#define PLUGIN_CALL __cdecl
#if defined(PLUGIN_EXPORT)
#define PLUGIN_API EXTERN_C __declspec(dllexport)
#define PLUGIN_CPP_API __declspec(dllexport)
#else
#define PLUGIN_API EXTERN_C __declspec(dllimport)
#define PLUGIN_CPP_API __declspec(dllimport)
#endif
#elif defined(__APPLE__)
#if AGORA_GCC_VERSION_AT_LEAST(3, 3)
#define PLUGIN_API __attribute__((visibility("default"))) EXTERN_C
#define PLUGIN_CPP_API __attribute__((visibility("default")))
#else
#define PLUGIN_API EXTERN_C
#define PLUGIN_CPP_API
#endif
#define PLUGIN_CALL
#elif defined(__ANDROID__) || defined(__linux__)
#if AGORA_GCC_VERSION_AT_LEAST(3, 3)
#define PLUGIN_API EXTERN_C __attribute__((visibility("default")))
#define PLUGIN_CPP_API __attribute__((visibility("default")))
#else
#define PLUGIN_API EXTERN_C
#define PLUGIN_CPP_API
#endif
#define PLUGIN_CALL
#else
#define PLUGIN_API EXTERN_C
#define PLUGIN_CPP_API
#define PLUGIN_CALL
#endif

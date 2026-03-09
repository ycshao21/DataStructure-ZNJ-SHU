#pragma once

#if defined(_WIN32) || defined(__WIN32__)

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

#elif defined(__linux__)
#include <unistd.h>
#else
#error "Unsupported platform"
#endif

#if defined(_WIN32) || defined(__WIN32__)

#if defined(UTILS_EXPORT)
#define UTILS_API __declspec(dllexport)
#elif defined(UTILS_IMPORT)
#define UTILS_API __declspec(dllimport)
#else
#define UTILS_API
#endif

#elif defined(__linux__)

#if defined(UTILS_EXPORT)
#define UTILS_API __attribute__((visibility("default")))
#else
#define UTILS_API
#endif

#else
#error "Unsupported platform"
#endif
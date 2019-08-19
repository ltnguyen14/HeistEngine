#pragma once
#include "cstdint"

#ifdef HEIST_PLATFORM_WINDOWS
	#ifdef HEIST_BUILD_DLL
		#define HEIST_API __declspec(dllexport)
	#else
		#define HEIST_API __declspec(dllimport)
	#endif
	#define HS_ARRAY_COUNT(arr) (sizeof(arr) / sizeof(arr[0]))
#else
	#error Engine only supports Windows
#endif

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float real32;
typedef double real64;

// CONSTANTS

constexpr auto Pi = 3.14159265359f;